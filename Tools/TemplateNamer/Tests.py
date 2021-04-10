#!/usr/bin/python

# Simple unittests set for TemplateNamer
import sys
import unittest
import TemplateNamer


class TestTemplateNamer(unittest.TestCase):
    def test_without_args(self):
        has_error = False
        try:
            TemplateNamer.main([])
        except sys.stderr:
            has_error = True
        self.assertTrue(has_error)

    def test_validate_name(self, args=None):
        if args is None:
            args = ['good_new_name']
        has_error = False
        try:
            TemplateNamer.main(args)
        except sys.stderr:
            has_error = True
        self.assertTrue(has_error)

    def test_invalid_set_names(self):
        self.test_validate_name(['-n', 'invalid', 'name'])
        self.test_validate_name(['--name="invalid', 'name"'])
        self.test_validate_name(['--name=invalid', 'name'])
        self.test_validate_name(['--name="invalid$\"name"'])
        # TODO:
