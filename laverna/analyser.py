from clang.cindex import *
import difflib


class CodeAnalyser:

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


class CodeSimilarityTool:
    def __cursor_kind_list_filter__(self, cursors, kinds_to_filter=[]):
        """
        CursorKind.COMPOUND_STMT - Remove braces (helps to better recognized code like this:
        #1:
        if (variable == 1)
            return 1;
        #2
        if (variable == 1)
        {
            return 1;
        }


        """
        return list(filter(lambda c: c not in kinds_to_filter, cursors))


    def __get_flatten_cursors_kinds__(self, cursor, code_unit, depth=0):
        # print('-' * depth, 'L:', cursor.location.line, 'type:', cursor.kind, 'name:', cursor.displayname, )
        # if depth <= 3:
        #     print(' ' * depth, cursor.kind, cursor.displayname)
        # if depth is 0:
        kinds = [cursor.kind]

        for c in cursor.get_children():
            kinds += self.__get_flatten_cursors_kinds__(c, code_unit, depth + 1)

        return kinds

    def __prepare_top_level_cursors__(self, code_unit):
        # print(code_unit)

        # global_cursors = [cursor for cursor in code_unit.cursors
        #                           if cursor.kind not in {CursorKind.FUNCTION_DECL, CursorKind.STRUCT_DECL}
        #                           or (cursor.kind in {CursorKind.FUNCTION_DECL,
        #                                               CursorKind.STRUCT_DECL} and cursor.is_definition())]
        # Remove declaration nodes from tree on top level to simplifying ratio computing
        global_cursors = [cursor for cursor in code_unit.cursors
                          if cursor.kind not in {CursorKind.FUNCTION_DECL, CursorKind.STRUCT_DECL}
                          or (cursor.kind is CursorKind.FUNCTION_DECL and cursor.is_definition())]

        # sort by displayname beacuse mangled_name could have too small information
        # (ex, add(const char *, const char *, char **) vs add)
        global_cursors.sort(key=lambda c: c.displayname)

        return global_cursors

    def __prepare_cursors_from_code_unit__(self, code_unit):
        cursors = []
        # print(code_unit)
        for c in self.__prepare_top_level_cursors__(code_unit):
            cursors += self.__get_flatten_cursors_kinds__(c, code_unit)

        return self.__cursor_kind_list_filter__(cursors, [CursorKind.COMPOUND_STMT])

    def simple_similarity_ratio(self, code_unit_a, code_unit_b):
        """
            Only for simple code. Vulnerable for dividing code into separate, multiple functions
        """
        a_tags = self.__prepare_cursors_from_code_unit__(code_unit_a)
        b_tags = self.__prepare_cursors_from_code_unit__(code_unit_b)

        ab_ratio = difflib.SequenceMatcher(a=a_tags, b=b_tags).ratio()
        ba_ratio = difflib.SequenceMatcher(a=b_tags, b=a_tags).ratio()

        if ab_ratio != ba_ratio: print("MAX ", max(ab_ratio, ba_ratio), "AB", ab_ratio, "BA", ba_ratio)
        return max(ab_ratio, ba_ratio)

    def functions_similarity_ratio(self, code_unit_a, code_unit_b):
        temp_cursors_a = self.__prepare_top_level_cursors__(code_unit_a)
        temp_cursors_b = self.__prepare_top_level_cursors__(code_unit_b)

        get_mutual = lambda a, b: [ca for ca in a if ca.displayname in [cb.displayname for cb in b]]
        get_diff = lambda a, b: [ca for ca in a if ca.displayname not in [cb.displayname for cb in b]]

        global_cursors_a = get_mutual(temp_cursors_a, temp_cursors_b) + get_diff(temp_cursors_a, temp_cursors_b)
        global_cursors_b = get_mutual(temp_cursors_b, temp_cursors_a) + get_diff(temp_cursors_b, temp_cursors_a)

        # print([c.displayname for c in global_cursors_a])
        # print([c.displayname for c in global_cursors_b])

        ratios = []
        for i in range(min(len(global_cursors_a), len(global_cursors_b))):
            kinds_a = self.__cursor_kind_list_filter__(self.__get_flatten_cursors_kinds__(global_cursors_a[i], code_unit_a), [CursorKind.COMPOUND_STMT])
            kinds_b = self.__cursor_kind_list_filter__(self.__get_flatten_cursors_kinds__(global_cursors_b[i], code_unit_b), [CursorKind.COMPOUND_STMT])

            ab_ratio = difflib.SequenceMatcher(a=kinds_a,b=kinds_b).ratio()
            ba_ratio = difflib.SequenceMatcher(a=kinds_b,b=kinds_a).ratio()

            ratios.append([max(ab_ratio, ba_ratio), global_cursors_a[i].mangled_name])

        return ratios


    def complex_similarity_ratio(self, code_unit_a, code_unit_b):
        r = self.functions_similarity_ratio(code_unit_a, code_unit_b)
        return sum([i[0] for i in r])/len(r)












'''
    def __get_flatten_cursors_kinds__(self, cursor, code_unit, depth=0, unwind=False):
        # print('-' * depth, 'L:', cursor.location.line, 'type:', cursor.kind, 'name:', cursor.displayname, )
        # if depth <= 3:
        #     print(' ' * depth, cursor.kind, cursor.displayname)
        # if depth is 0:
        kinds = []
        # If unwind param is set True, then when it encounters the function call in the code, it will be expanded
        if unwind and CursorKind.CALL_EXPR is cursor.kind :
            """
            Fragment drzewa AST z wywołaniem funkcji
                CursorKind.VAR_DECL a
                !      CursorKind.CALL_EXPR sampleFunction
                     ----
                     CursorKind.FUNCTION_DECL sampleFunction(int, int)
                      CursorKind.PARM_DECL a
                      CursorKind.PARM_DECL b
                      CursorKind.COMPOUND_STMT 
                       CursorKind.RETURN_STMT 
                        CursorKind.BINARY_OPERATOR 
                         CursorKind.UNEXPOSED_EXPR a
                          CursorKind.DECL_REF_EXPR a
                         CursorKind.UNEXPOSED_EXPR b
                          CursorKind.DECL_REF_EXPR b
                     ----
            Pomiedzy ---- znajduje się rozwinięcie funkcji, która dodaje dwa inty i zwraca wynik.
                CursorKind.VAR_DECL a
                 CursorKind.BINARY_OPERATOR 
                  CursorKind.UNEXPOSED_EXPR a
                   CursorKind.DECL_REF_EXPR a
                  CursorKind.UNEXPOSED_EXPR b
                   CursorKind.DECL_REF_EXPR b
            To samo, tylko bez wywołania funkcji
            Aby upodobnić kod, do odpowiadającemu mu kodowi bez wywołania funkcji
            musimy usunąć tagi: FUNCTION_DECL, PARAM_DECL COMPOUND_STMT oraz RETURN_STMT
            """

            #
            # print(' ' * depth, cursor.kind, cursor.displayname, "       !+")
            # print(' ' * depth,"----")
            # for cf in cursor.referenced.get_children():
            #     if cf.kind not in []
            # unwind_stack = self.__get_flatten_cursors_kinds__(cursor.referenced, code_unit, depth + 1)
            kinds = self.__get_flatten_cursors_kinds__(cursor.referenced, code_unit, depth, unwind)
            kinds = self.__cursor_kind_list_filter__(kinds, [CursorKind.PARM_DECL, CursorKind.FUNCTION_DECL,
                                                             CursorKind.RETURN_STMT , CursorKind.COMPOUND_STMT])
            # kinds = list(filter(lambda k : k is not ))
            # kinds += self.__cursor_kind_list_filter__(unwind_stack, [CursorKind.COMPOUND_STMT])
            # print(' ' * depth,"----")
        else:
            # print(' ' * depth, cursor.kind, cursor.displayname)
            kinds = [cursor.kind]

        for c in cursor.get_children():
            kinds += self.__get_flatten_cursors_kinds__(c, code_unit, depth + 1)

        return kinds
'''