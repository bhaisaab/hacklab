#!/usr/bin/python
import sys
import os.path
import unittest
sys.path.insert(0, os.path.realpath(os.path.join(os.path.dirname(__file__), "..")))

from gopu import AboutGopuDialog

class TestExample(unittest.TestCase):
    def setUp(self):
        self.AboutGopuDialog_members = [
        'AboutGopuDialog', 'get_builder', 'gettext', 'gtk']

    def test_AboutGopuDialog_members(self):
        all_members = dir(AboutGopuDialog)
        public_members = [x for x in all_members if not x.startswith('_')]
        public_members.sort()
        self.assertEqual(self.AboutGopuDialog_members, public_members)

if __name__ == '__main__':    
    unittest.main()
