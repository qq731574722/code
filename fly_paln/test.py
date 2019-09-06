# -*- coding: utf-8 -*-

from main import sum
import unittest


class Test(unittest.TestCase):
    def test_sum(self):
        self.assertEqual(sum(1, 2), 3)

    def test_sum_1(self):
        self.assertEqual(sum(0.2, 0.2), 0.4)

    def test_sum_2(self):
        self.assertEqual(sum(10, 0.1), 10.1)


if __name__ == '__main__':
    unittest.main()
