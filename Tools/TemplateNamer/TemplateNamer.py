#!/usr/bin/python

# TemplateNamer - script for generating a new Slate UI stand alone project based on a template

import sys
import getopt
import os


key_replacing_name = 'UnrealSlateAppTemplate'



def is_valid_path(path):
    if not os.path.exists(path):
        return False, f'The specified path "{path}" does not exist.'
    return True, None


def parse_args(argv):
    project_name = ''
    project_path = ''

    help_msg = 'Usage: \tTemplateNamer.py ' \
               '[-n <project_name> | --name="<project_name>"] ' \
               '[-p <project_path> | --path="<project_path>"] ' \
               '[-h | --help]\n'

    try:
        opts, args = getopt.getopt(argv, "hn:p:i", ["name=", "path=", "interactive"])
    except getopt.GetoptError:
        print('Bad option(s)\n')
        print(help_msg)
        sys.exit(3)

    if ('-i', '') in opts or ('--interactive', '') in opts:
        input_str = input('<< Please enter a NAME for the new project:\n>> ')
        # print(f'{input_str}\n')
        project_name = input_str

        input_str = input('<< Please enter the PATH for the new project:\n>> ')
        # print(f'{input_str}\n')
        is_valid, error = is_valid_path(input_str)
        if not is_valid:
            print(f'[ERROR] {error}\n')
            sys.exit(3)
        project_path = input_str
        return project_name, project_path

    for opt, arg in opts:
        if opt == '-h':
            print(help_msg)
            sys.exit()

        if opt == '-n' or opt == '--name':
            if arg.startswith('"') and arg.endswith('"'):
                arg = arg[1:-1]
            project_name = arg

        if opt == '-p' or opt == '--path':
            if arg.startswith('"') and arg.endswith('"'):
                arg = arg[1:-1]
            is_valid, error = is_valid_path(arg)
            if not is_valid:
                print(f'[ERROR] {error}\n')
                sys.exit(3)
            project_path = arg

    return project_name, project_path


def get_dst_name_by_src_path(path, target_name):
    src_base_name = os.path.basename(path)
    if key_replacing_name in src_base_name:
        src_base_name = src_base_name.replace(key_replacing_name, target_name)
    return src_base_name


def read_src_and_write_dst_file(path, target_path, target_name):
    dst_file_name = get_dst_name_by_src_path(path, target_name)
    dst_path = os.path.join(target_path, dst_file_name)

    try:
        with open(path, 'r') as src_file:
            with open(dst_path, 'w') as dst_file:
                src_content = src_file.read()
                dst_content = src_content.replace(key_replacing_name, target_name)
                dst_file.write(dst_content)
    except:
        print("F! Creation of the file %s failed" % dst_path)
        return False
    else:
        print("F+ Successfully created the file %s " % dst_path)
    return True


def iterate_by_dir_content(dir_path, target_path, target_name):
    dst_dir_name = get_dst_name_by_src_path(dir_path, target_name)
    dst_path = os.path.join(target_path, dst_dir_name)
    if not os.path.exists(dst_path):
        try:
            os.mkdir(dst_path)
        except OSError:
            print("D! Creation of the directory %s failed" % dst_path)
            return False
        else:
            print("D+ Successfully created the directory %s " % dst_path)

    for item in os.listdir(dir_path):
        item_path = os.path.join(dir_path, item)
        if os.path.isdir(item_path):
            if not iterate_by_dir_content(item_path, dst_path, target_name):
                return False
        else:
            if not read_src_and_write_dst_file(item_path, dst_path, target_name):
                return False
    return True


def create_empty_slate_project(name, path):
    target_root = os.path.join(path, name)
    try:
        os.mkdir(target_root)
    except OSError:
        print("D! Creation of the directory %s failed" % target_root)
        return False
    else:
        print("D+ Successfully created the directory %s " % target_root)

    # detect the current working directory and print it
    tool_path = os.getcwd()
    template_path = os.path.join(tool_path, "../../")

    is_success = iterate_by_dir_content(os.path.join(template_path, "Source"), target_root, name)
    is_success &= read_src_and_write_dst_file(os.path.join(template_path, f'{key_replacing_name}.uproject'), target_root, name)

    return is_success


def main(argv):
    name, path = parse_args(argv)
    print(f'--- Creating "{name}" to "{path}"...')
    if create_empty_slate_project(name, path):
        print(f'--- Done! ---')
    else:
        print(f'--- Failed. ---')


if __name__ == "__main__":
    main(sys.argv[1:])
