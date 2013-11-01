#!/usr/bin/python

import inspect
import os
from random import randint, random
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
class AnotherEnigmaGenerator(Generator):
    YES_PROP = 0.1
    SMALL_PROP = 0.2

    def __init__(self, input_file=None, output_file=None, *args, **kwargs):
        super(AnotherEnigmaGenerator, self).__init__(*args, **kwargs)

    def _print_line(self, line_format, *args, **kwargs):
        print(line_format % args)

    def _generate_test_case_helper(
        self, max_n, min_n, max_q, min_q, max_m, min_m):

        n = randint(min_n, max_n)
        v = self.gen_int_sequence(n, 1, 10 ** 4)
        q = randint(min_q, max_q)

        self._print_line('%d', *(n, ))
        self._print_line(' '.join(map(lambda x: str(x), v)))
        self._print_line('%d', *(q, ))

        for _ in xrange(q):
            if (random() <= self.YES_PROP):
                # Take a random sample from v.
                n1 = randint(1, n) - 1
                n2 = min(n, n1 + randint(min_m, max_m))
                # FIXME: Can be less than min_m
                m = n2 - n1
                w = v[n1: n2]
            else:
                # Probably NO.
                m = randint(min_m, max_m)
                w = self.gen_int_sequence(m, 1, 10 ** 4)

            self._print_line('%d', *(m, ))
            self._print_line(' '.join(map(lambda x: str(x), w)))

    def generate_test_case(self, *args, **kwargs):
        if (random() < self.SMALL_PROP):
            self._generate_test_case_helper(10 ** 2, 1, 20, 1, 5 * (10 ** 2), 1)
        else:
            # These are counter examples for KMP and naive SA.
            self._generate_test_case_helper(
                100000, 50000, 1000, 500, 1000, 500)

    def generate_test_cases(self, n, add_sample=True, *args, **kwargs):
        if (add_sample):
            # FIXME: Clowntown.
            self._print_line('%d', *(n + 2, ))
            self._print_line('4')
            self._print_line('1 5 4 2')
            self._print_line('3')
            self._print_line('3')
            self._print_line('1 5 4')
            self._print_line('2')
            self._print_line('1 4')
            self._print_line('3')
            self._print_line('2 4 5')
            self._print_line('7')
            self._print_line('1 2 3 4 5 7 6')
            self._print_line('1')
            self._print_line('7')
            self._print_line('1 2 3 4 5 7 6')
        else:
            self._print_line('%d', *(n, ))

        for _ in xrange(n):
            self.generate_test_case()


def main():
    gen = AnotherEnigmaGenerator()
    gen.generate_test_cases(5)

if __name__ == '__main__':
    main()
