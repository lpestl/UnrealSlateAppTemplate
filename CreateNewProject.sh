#!/bin/sh

echo "-----"
BASEDIR=$(dirname "$0")

if ! python3 -c 'import sys; assert sys.version_info >= (3,6)' > /dev/null; then
    echo Python3 is not installed. Install Python3 to run the script.
    echo "-----"
    exit 1
fi

cd $BASEDIR/Tools/TemplateNamer/
python3 TemplateNamer.py -i

echo "-----"
