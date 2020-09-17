from clang.cindex import *

standard_library = ('stdio.h', 'stdlib.h', 'corecrt.h', 'string.h', 'sal.h', 'concurrencysal.h',
                    'corecrt_malloc.h', 'vcruntime.h', 'ctype.h', 'math.h', 'corecrt_wstdio.h', 'corecrt_memcpy_s.h',
                    'corecrt_stdio_config.h', 'corecrt_malloc.h', 'corecrt_wstdlib.h', 'limits.h',
                    'corecrt_memory.h', 'errno.h', 'vcruntime_string.h', 'corecrt_wstring.h',
                    'corecrt_wctype.h', 'corecrt_math.h',
                    'vadefs.h', 'stddef.h', 'corecrt_search.h')


class ParseUnit:

    def __init__(self, filename, excluded_headers=()):
        # Initialize ParseUnit object. It takes a path to source file and optional list
        # with excluded headers from parsing. If this list is empty, default headers will be set.

        self.filename = filename

        if any(excluded_headers):
            self.include_to_filter = standard_library
        else:
            self.include_to_filter = excluded_headers

        self.tu = TranslationUnit
        self.filt_curs = []

    def parse(self):
        # Parse file.

        # print('Processing', self.filename, '...')
        # create index
        index = Index.create()
        # parse file
        self.tu = index.parse(self.filename)

        if not self.tu:
            print('Wrong input!')
            return False

        # print('Translation unit:', self.tu.spelling)
        # for c in self.tu.cursor.get_children():
        #     if not c.location.file.name.endswith(standard_library):
        #         self.filt_curs.append(c)
        #
        for c in self.tu.cursor.get_children():
            if c.location.file.name.endswith(self.filename): #TODO check only filename, not whole path
                self.filt_curs.append(c)

        return True

    def __dump_cursor_kind__(self, cursor, depth=0):
        # print('--' * depth, 'Line:', cursor.location.line, 'type:', cursor.kind, 'name:', cursor.displayname, )
        print(cursor.kind)
        for c in cursor.get_children():
            self.__dump_cursor_kind__(c, depth + 1)

    def __gather_cursor_kind__(self, cursor, depth=0):
        # print('-' * depth, 'L:', cursor.location.line, 'type:', cursor.kind, 'name:', cursor.displayname, )
        # print('-' * depth, cursor.kind, 'name:', cursor.displayname, )
        retVal = [cursor.kind]
        for c in cursor.get_children():
            retVal += self.__gather_cursor_kind__(c, depth + 1)
        return retVal

    def __dump_cursor__(self, cursor, depth=0):
        print('-' * depth, 'L:', cursor.location.line, 'type:', cursor.kind, 'name:', cursor.displayname, )
        # print(cursor.kind )
        # for c in cursor.get_children():
        #     self.__dump_cursor__(c, depth + 1)

    def dump(self):
        # Dump dumped cursors. It's not whole AST tree, only simplified tree.

        for c in self.filtered_cursors:
            self.__dump_cursor__(c)

    def dump_cursors_kind(self):
        for c in self.filtered_cursors:
            self.__dump_cursor_kind__(c)

    def get_cursors_kind(self):
        retVal = []
        for c in self.filtered_cursors:
            retVal += self.__gather_cursor_kind__(c)
        return retVal

    def get_prepared_cursors_kind(self):
        retVal = []

        pre_filtered_main_cursors = [node for node in self.filtered_cursors if node.kind  in {CursorKind.FUNCTION_DECL, CursorKind.STRUCT_DECL} and node.is_definition()]
        pre_filtered_main_cursors.sort(key=lambda c: c.displayname)

        for c in pre_filtered_main_cursors:
            # print(c.displayname)
            retVal += self.__gather_cursor_kind__(c)



        #testing
        return list(filter(lambda kind:kind not in {CursorKind.STRING_LITERAL, CursorKind.INTEGER_LITERAL}, retVal ))
        # return retVal

    def get_all_additional_includes(self):
        # Return array with tuples(depth and absolute path) with includes from current parse unit.
        # It returns ALL includes, including headers from standard library, etc.
        additional_includes = []
        for include in self.translation_unit.get_includes():
            additional_includes.append((include.depth, include.include))

        return additional_includes

    @property
    def filtered_cursors(self):
        return self.filt_curs

    @property
    def translation_unit(self):
        return self.tu
