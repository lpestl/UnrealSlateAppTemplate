@Echo off

echo -----

pushd %~dp0%

:: Check for Python Installation
python -c "import sys; assert sys.version_info >= (3,6)" 2>NUL
if errorlevel 1 (
    echo Error^: Python3 is not installed. Install Python3 to run the script.
    echo -----
    goto:eof
)

cd Tools/TemplateNamer/

python TemplateNamer.py -i

popd

echo -----