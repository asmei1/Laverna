from clang.cindex import *
import difflib


class Analyzer:
    def __init__(self):
        pass

    def __filter_cursor__(self, cursor, filter_fun):
        filtered = []

        if filter_fun(cursor):
            filtered.append(cursor)

        for c in cursor.get_children():
            filtered += self.__filter_cursor__(c, filter_fun)

        return filtered

    def __filter_parse_unit_cursor_list__(self, cursor_list, filter_fun):
        cursors = []
        for c in cursor_list:
            cursors += self.__filter_cursor__(c, filter_fun)

        return cursors


    def find_array_operators(self, parse_unit):
        array_operators = []
        for c in self.__filter_parse_unit_cursor_list__(parse_unit.filtered_cursors, lambda cur: cur.kind is CursorKind.ARRAY_SUBSCRIPT_EXPR):
            array_operators.append((c.location.file, c.location.line))

        return array_operators

    def find_structers(self, parse_unit):
        array_operators = []
        for c in self.__filter_parse_unit_cursor_list__(parse_unit.filtered_cursors, lambda cur: cur.kind is CursorKind.STRUCT_DECL):
            array_operators.append((c.location.file, c.location.line, c.displayname))

        return array_operators

    def find_global_variables(self, parse_unit):
        # If variable is on 'first level' of cursors, it should be a global variable.

        global_variables_list = []
        for n in parse_unit.filtered_cursors:
            if n.kind is CursorKind.VAR_DECL:
                global_variables_list.append((n.location.file, n.location.line, n.displayname))

        return global_variables_list

    def get_comments(self, parse_unit):
        # not working
        commnents = []
        for c in self.__filter_parse_unit_cursor_list__(parse_unit.filtered_cursors, lambda cur: True):
            if not c.raw_comment:
                commnents.append(c.raw_comment)
                commnents.append(c.brief_comment)
        return commnents

    def compute_similarity_ratio(self, parse_unit_a, parse_unit_b):
        # A = ' '.join(str(node)[11:] for node in parse_unit_a.get_cursors_kind())
        # B = ' '.join(str(node)[11:] for node in parse_unit_b.get_cursors_kind())
        # return difflib.SequenceMatcher(a=A, b=B).ratio()

        # A = ' '.join(str(node.value) for node in parse_unit_a.get_cursors_kind())
        # B = ' '.join(str(node.value) for node in parse_unit_b.get_cursors_kind())
        # return difflib.SequenceMatcher(a=A, b=B).ratio()
        a_kinds = parse_unit_a.get_cursors_kind()
        b_kinds = parse_unit_b.get_cursors_kind()

        filterFunction = lambda node: node is not (CursorKind.STRUCT_DECL or CursorKind.FIELD_DECL or CursorKind.VAR_DECL or CursorKind.FUNCTION_DECL or CursorKind.TYPEDEF_DECLor or CursorKind.MACRO_DEFINITION )

        a_kinds = list(filter(filterFunction, a_kinds))
        b_kinds = list(filter(filterFunction, b_kinds))

        return difflib.SequenceMatcher(a=a_kinds, b=b_kinds).ratio()



'''
    log_file = open('dump.txt', 'w')
    for c in filter_cursor:
        log_file.write('Displayname:' + c.displayname)
        log_file.write('\n')
        log_file.write('Spelling:' + c.spelling)
        log_file.write('\n')
        log_file.write('get_usr:' + c.get_usr())
        log_file.write('\n')
        log_file.write('Kind:' + c.get_usr())
        log_file.write('\n')
        log_file.write('mangled_name:' + c.mangled_name)
        log_file.write('\n')
        log_file.write('location:' + c.location.file.name)
        log_file.write('\n')

        log_file.write('-------------------------------------------------------------------\n')

        print(c.displayname, '\t|\t',  c.spelling)
    log_file.flush()
    log_file.close()
'''
