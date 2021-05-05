#!/usr/bin/python

# Simple unittests set for TemplateNamer
import sys
import unittest
import TemplateNamer


class TestTemplateNamer(unittest.TestCase):
    def test_without_args(self):
        has_error = False
        try:
            TemplateNamer.parse_args([])
        except sys.stderr:
            has_error = True
        self.assertTrue(not has_error)

    def test_validate_name(self, args=None, must_be_error=False):
        if args is None:
            args = ['good_new_name']
        has_error = False
        try:
            TemplateNamer.parse_args(args)
        except:
            has_error = True
        self.assertTrue(must_be_error == has_error)

    def test_invalid_set_names(self):
        self.test_validate_name(['--name="invalid$\"name"'], True)
        self.test_validate_name(['--name="invalid_name"'], False)
        self.test_validate_name(['--name="invalid"name"'], True)
        self.test_validate_name(['--name="invalid%name"'], True)
        self.test_validate_name(['--name="<invalid_name>"'], True)
        self.test_validate_name(['--name="invalid!name"'], True)
        self.test_validate_name(['--name="invalid?name"'], True)
        self.test_validate_name(['--name="invalid&name"'], True)
        self.test_validate_name(['--name="invalid^name"'], True)
        self.test_validate_name(['--name="invalid*name"'], True)
        self.test_validate_name(['--name="invalid\\name"'], True)
        self.test_validate_name(['--name="invalid/name"'], True)
        self.test_validate_name(['--name="invalid:name"'], True)
        self.test_validate_name(['--name="invalid!name"'], True)
        # TODO:
