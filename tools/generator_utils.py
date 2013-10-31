#!/usr/bin/python

from random import randint, shuffle

# First version of my custom test cases generator.
class Generator(object):
    SMALL_THRESHOLD = None

    def __init__(self, small_threshold=100, *args, **kwargs):
        self.SMALL_THRESHOLD = small_threshold

    def _gen_unique_small(self, n, elems, *args, **kwargs):
        shuffle(elems)

        return elems[: n]

    def _gen_unique_large(self, n, generator, *args, **kwargs):
        ans = []
        ap_function = ans.append
        used = set([])
        add_function = used.add
        while (n > 0):
            elem = generator()
            if elem not in used:
                add_function(elem)
                ap_function(elem)

                n -= 1

        return ans

    def _gen_sequence(self, n, generator):
        return [generator() for _ in xrange(n)]

    def gen_int_sequence(
        self, n, min_elem, max_elem, unique=False, *args, **kwargs):

        if (n < 0):
            raise Exception('Bla')

        if (min_elem > max_elem):
            raise Exception('Bla')

        if (n > (max_elem - min_elem + 1) and unique):
            raise Exception('Bla')

        if (not unique):
            return self._gen_sequence(n, lambda: randint(min_elem, max_elem))

        diff = max(0, n - (max_elem - min_elem + 1))
        if (diff > self.SMALL_THRESHOLD):
            return self._gen_unique_large(
                n, lambda: randint(min_elem, max_elem), *args, **kwargs
            )

        return self._gen_unique_small(
            n, range(min_elem, max_elem + 1), *args, **kwargs
        )

    def generate_test_case(self, *args, **kwargs):
        raise NotImplemented('Implement generate_test_case')

    def generate_test_cases(self, *args, **kwargs):
        raise NotImplemented('Implement generate_test_cases')
