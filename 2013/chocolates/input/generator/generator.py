#!/usr/bin/python

import inspect
import os
from random import randint
import sys

# FIXME: Move to conf.
TOOLS_DIR = \
    os.path.realpath(
        os.path.abspath(
            os.path.split(
                inspect.getfile(
                    inspect.currentframe()
                )
            )[0]
        )
    )
TOOLS_DIR = \
    os.path.join('/'.join(TOOLS_DIR.split('/')[0: -4]), 'tools')

sys.path.append(TOOLS_DIR)

from generator_utils import Generator

# TODO: Add methods for input/output files support.
class ChocolatesGenerator(Generator):
    def __init__(self, input_file=None, output_file=None, *args, **kwargs):
        super(ChocolatesGenerator, self).__init__(*args, **kwargs)

    def _print_line(self, line_format, *args, **kwargs):
        print(line_format % args)

    def generate_test_case(self, *args, **kwargs):
        n = randint(1, 10 ** 9)
        m = randint(1, 20)
        l = self.gen_int_sequence(m, 1, 20, unique=True, *args, **kwargs)

        self._print_line('%d %d', *(n, m))
        self._print_line(' '.join(map(lambda x: str(x), l)))

    def generate_test_cases(self, n, add_sample=True, *args, **kwargs):
        if (add_sample):
            # FIXME: Clowntown.
            self._print_line('%d', *(n + 4, ))
            self._print_line('4 3')
            self._print_line('1 2 3')
            self._print_line('10 2')
            self._print_line('2 8')
            self._print_line('1000000 1')
            self._print_line('3')
            self._print_line('10000 2')
            self._print_line('1 2')
        else:
            self._print_line('%d', *(n, ))

        for _ in xrange(n):
            self.generate_test_case(*args, **kwargs)


def main():
    gen = ChocolatesGenerator()
    gen.generate_test_cases(1000)

if __name__ == '__main__':
    main()
