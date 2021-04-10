#!/usr/bin/python

# TemplateNamer - script for generating a new Slate UI stand alone project based on a template

import sys
import getopt

validate_name_error = 'The name entered must not include special characters or line separators. ' \
                      'Please choice another name and try again.'


def is_valid_name(name):
    return False


def parse_args(argv):
    project_name = ''
    project_path = ''

    help_msg = 'Usage: \tTemplateNamer.py ' \
               '[-n <project_name> | --name="<project_name>"] ' \
               '[-p <project_path> | --path="<project_path>"] ' \
               '[-h | --help]\n'

    try:
        opts, args = getopt.getopt(argv, "hn:p:", ["name=", "path="])
    except getopt.GetoptError:
        print('Bad option(s)\n')
        print(help_msg)
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-h':
            print(help_msg)
            sys.exit()
        if opt == '-n' or opt == '--name':
            print(arg)
            if not is_valid_name(arg):
                print(f'[ERROR] {validate_name_error}')
                sys.exit(3)
            project_name = arg

    return project_name, project_path


def main(argv):
    name, path = parse_args(argv)
    print(f'Generate {name} to {path}')


if __name__ == "__main__":
    main(sys.argv[1:])
