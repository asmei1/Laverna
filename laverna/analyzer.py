from clang.cindex import *


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

    def find_global_variables(self, parse_unit):
        """If variable is on 'first level' of cursors, it should be a global variable. """
        global_variables_list = []
        for n in parse_unit.filtered_cursors:
            if n.kind is CursorKind.VAR_DECL:
                global_variables_list.append((n.location.file, n.location.line, n.displayname))

        return global_variables_list

    #not working
    def get_comments(self, parse_unit):
        commnents = []
        for c in self.__filter_parse_unit_cursor_list__(parse_unit.filtered_cursors, lambda cur: True):
            if not c.raw_comment:
                commnents.append(c.raw_comment)
                commnents.append(c.brief_comment)
        return commnents
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
