from clang.cindex import *

standard_library = ('stdio.h', 'stdlib.h', 'corecrt.h',
                    'corecrt_malloc.h', 'vcruntime.h',
                    'vadefs.h', 'stddef.h', 'corecrt_search.h')
class ParseUnit:

    def __init__(self, filename, includes_to_filter=()):
        self.filename = filename

        if any(includes_to_filter):
            self.include_to_filter = standard_library
        else:
            self.include_to_filter = includes_to_filter

        self.tu = TranslationUnit
        self.filt_curs = []

    def parse(self):
        print('Processing', self.filename, '...')
        # create index
        index = Index.create()
        # parse file
        self.tu = index.parse(self.filename)

        if not self.tu:
            print('Wrong input!')
            return False

        print('Translation unit:', self.tu.spelling)
        for c in self.tu.cursor.get_children():
            if not c.location.file.name.endswith(standard_library):
                self.filt_curs.append(c)

        return True

    def __dumpCursor__(self, cursor, depth=0):
        print('--' * depth, 'Line:', cursor.location.line, 'type:', cursor.kind, 'name:', cursor.displayname, )
        for c in cursor.get_children():
            self.__dumpCursor__(c, depth + 1)

    def dump(self):
        for c in self.filtered_cursors:
            self.__dumpCursor__(c)

    def get_all_additional_includes(self):
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