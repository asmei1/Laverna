from clang.cindex import *
import logging, sys, os

logging.basicConfig(stream=sys.stderr, level=logging.ERROR)


class CodeUnit:

    def __init__(self, filenames):
        # Initialize ParseUnit object. It receive a list of files, which will be parsed

        self._all_cursors = []
        self._translation_units = []

        logging.debug('Code unit processing ...')

        for filename in filenames:
            # Parse file.
            logging.debug('Processing ' + filename + ' ...')
            # create index
            index = Index.create()
            # parse file
            self._translation_units.append(index.parse(filename))

        for tu in self._translation_units:
            for node in tu.cursor.get_children():
                if os.path.basename(node.location.file.name) in [os.path.basename(fn) for fn in filenames]:
                    self._all_cursors.append(node)

        logging.debug('Code unit parsed.')


    def __dump_cursor__(self, cursor, depth=0):
        print('-' * depth, 'L:', cursor.location.line, 'type:', cursor.kind, 'name:', cursor.displayname, )
        for c in cursor.get_children():
            self.__dump_cursor__(c, depth + 1)

    def print_dump(self):
        # Dump dumped cursors. It's not whole AST tree, only simplified tree.
        for c in self.cursors:
            self.__dump_cursor__(c)

    @property
    def translation_units(self):
        return self._translation_units

    @property
    def cursors(self):
        return self._all_cursors
