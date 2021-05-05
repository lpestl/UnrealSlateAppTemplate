#!/bin/sh

echo "-----"
BASEDIR=$(dirname "$0")
pushd $BASEDIR/Tools/TemplateNamer/ > /dev/null
python3 TemplateNamer.py -i
popd > /dev/null
echo "-----"
