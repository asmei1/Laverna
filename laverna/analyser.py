from clang.cindex import *
import difflib


class CodeAnalyser:
    # Similarity ratio compute options
    """
    SR_REMOVE_BRACES: remove braces tags from code (helps to better recognized code like this:
    #1:
    if (variable == 1)
        return 1;
    #2
    if (variable == 1)
    {
        return 1;
    }

    SR_SORT_GLOBALS_BY_NAME: sort global function declarations/definitions and global variables by their name

    SR_REMOVE_PATTERNS: Try to remove patterns, it should find and remove patterns putted to code to make harder
                        to detect plagiarisms
    SR_REMOVE_GLOBAL_DECL: Remove declarations node from tree

    SR_ALL: apply all rules
    """
    SR_REMOVE_BRACES = 1
    SR_SORT_GLOBALS_BY_NAME = 2
    SR_REMOVE_PATTERNS = 3
    SR_REMOVE_GLOBAL_DECLS = 4

    SR_ALL = 255

    def __init__(self):
        pass

    def __get_filtered_cursors__(self, cursor, filter_fun):
        filtered = []
        if filter_fun(cursor):
            filtered.append(cursor)

        for c in cursor.get_children():
            filtered += self.__get_filtered_cursors__(c, filter_fun)

        return filtered

    def __filter_parse_unit_cursor_list__(self, cursor_list, filter_fun):
        cursors = []
        for c in cursor_list:
            cursors += self.__get_filtered_cursors__(c, filter_fun)

        return cursors

    def find_array_operators(self, code_unit):
        array_operators = []
        for c in self.__filter_parse_unit_cursor_list__(code_unit.cursors,
                                                        lambda cur: cur.kind is CursorKind.ARRAY_SUBSCRIPT_EXPR):
            array_operators.append((c.location.file, c.location.line))

        return array_operators

    def find_for_loop(self, code_unit):
        loops = []
        for c in self.__filter_parse_unit_cursor_list__(code_unit.cursors,
                                                        lambda cur: cur.kind is CursorKind.FOR_STMT):
            loops.append((c.location.file, c.location.line))

        return loops

    def find_do_while_loop(self, code_unit):
        loops = []

        for c in self.__filter_parse_unit_cursor_list__(code_unit.cursors,
                                                        lambda cur: cur.kind is CursorKind.DO_STMT):
            loops.append((c.location.file, c.location.line))
        return loops

    def find_while_loop(self, code_unit):
        loops = []
        for c in self.__filter_parse_unit_cursor_list__(code_unit.cursors,
                                                        lambda cur: cur.kind is CursorKind.WHILE_STMT):
            loops.append((c.location.file, c.location.line))
        return loops

    def find_loops(self, code_unit):
        loops = []
        for c in self.__filter_parse_unit_cursor_list__(code_unit.cursors,
                                                        lambda cur: cur.kind in {CursorKind.FOR_STMT,
                                                                                 CursorKind.DO_STMT,
                                                                                 CursorKind.WHILE_STMT}):
            loops.append((c.location.file, c.location.line))
        return loops

    def find_goto(self, code_unit):
        gotos = []
        for c in self.__filter_parse_unit_cursor_list__(code_unit.cursors,
                                                        lambda cur: cur.kind is CursorKind.GOTO_STMT):
            gotos.append((c.location.file, c.location.line))
        return gotos

    def find_structs(self, code_unit):
        structs = []
        for c in self.__filter_parse_unit_cursor_list__(code_unit.cursors,
                                                        lambda cur: cur.kind is CursorKind.STRUCT_DECL):
            structs.append((c.location.file, c.location.line, c.displayname))

        return structs

    def find_global_variables(self, code_unit):
        # If variable is on 'first level' of cursors, it should be a global variable.

        global_variables = []
        for n in code_unit.cursors:
            if n.kind is CursorKind.VAR_DECL:
                global_variables.append((n.location.file, n.location.line, n.displayname))

        return global_variables

    def __get_flatten_cursors__(self, cursor, depth=0):
        # print('-' * depth, 'L:', cursor.location.line, 'type:', cursor.kind, 'name:', cursor.displayname, )
        # if depth <= 3:
        #     print(' ' * depth, cursor.kind, cursor.displayname)
        # if depth <= 0:
        #     print(' ' * depth, cursor.kind, cursor.displayname)
        kinds = [cursor]
        for c in cursor.get_children():
            kinds += self.__get_flatten_cursors__(c, depth + 1)
        return kinds

    def __prepare_cursors_from_code_unit__(self, code_unit, options):
        cursors = []
        # print(code_unit)
        global_cursors = [cursor for cursor in code_unit.cursors
                          if CodeAnalyser.SR_REMOVE_GLOBAL_DECLS not in options or cursor.is_definition()]

        if CodeAnalyser.SR_SORT_GLOBALS_BY_NAME in options:
            # sort by displayname (ex, add(const char *, const char *, char **)), beacuse mangled_name (ex. add)
            # could have too small information
            global_cursors.sort(key=lambda c: c.displayname)

        for c in global_cursors:
            cursors += self.__gather_cursors_kind__(c)

        if CodeAnalyser.SR_REMOVE_BRACES in options:
            cursors = list(filter(lambda c: c is not CursorKind.COMPOUND_STMT, cursors))

        return cursors

    def compute_similarity_ratio(self, code_unit_a, code_unit_b, options=[]):
        # check, if all rules option was enabled
        if CodeAnalyser.SR_ALL in options:
            options = [CodeAnalyser.SR_REMOVE_BRACES, CodeAnalyser.SR_SORT_GLOBALS_BY_NAME,
                       CodeAnalyser.SR_REMOVE_GLOBAL_DECLS, CodeAnalyser.SR_REMOVE_PATTERNS]

        a_tags = self.__prepare_cursors_from_code_unit__(code_unit_a, options)
        b_tags = self.__prepare_cursors_from_code_unit__(code_unit_b, options)

        ab_ratio = difflib.SequenceMatcher(a=a_tags, b=b_tags).ratio()
        ba_ratio = difflib.SequenceMatcher(a=b_tags, b=a_tags).ratio()

        if ab_ratio != ba_ratio: print("MAX ", max(ab_ratio, ba_ratio), "AB", ab_ratio, "BA", ba_ratio)
        return max(ab_ratio, ba_ratio)

    def __prepare_cursors__(self, code_unit, options):
        # print(code_unit)
        global_cursors = [cursor for cursor in code_unit.cursors if cursor.kind is CursorKind.FUNCTION_DECL and cursor.is_definition()]

        if CodeAnalyser.SR_SORT_GLOBALS_BY_NAME in options:
            global_cursors.sort(key=lambda c: c.displayname)

        return global_cursors

    def compute_func_sim(self, code_unit_a, code_unit_b):
        options =  [CodeAnalyser.SR_REMOVE_BRACES, CodeAnalyser.SR_SORT_GLOBALS_BY_NAME,
                       CodeAnalyser.SR_REMOVE_GLOBAL_DECLS]

        global_cursors_a = self.__prepare_cursors__(code_unit_a, options)
        global_cursors_b = self.__prepare_cursors__(code_unit_b, options)

        global_cursors_b = list(filter(lambda c : c.displayname in [ca.displayname for ca in global_cursors_a], global_cursors_b))
        global_cursors_a = list(filter(lambda c : c.displayname in [ca.displayname for ca in global_cursors_b], global_cursors_a))

        # print([c.displayname for c in global_cursors_a])
        # print([c.displayname for c in global_cursors_b])
        ratios = []
        for i in range(len(global_cursors_a)):
            ratios.append([difflib.SequenceMatcher(a=self.__gather_cursors_kind__(global_cursors_a[i]),
                                                   b=self.__gather_cursors_kind__(global_cursors_b[i])).ratio(), global_cursors_a[i].mangled_name])

        print(ratios)
        print(sum([r[0] for r in ratios]) / len(ratios))
        # ab_ratio = difflib.SequenceMatcher(a=a_tags, b=b_tags).ratio()
        # ba_ratio = difflib.SequenceMatcher(a=b_tags, b=a_tags).ratio()