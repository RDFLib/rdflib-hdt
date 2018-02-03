#!/usr/bin/env bash
# scripts for automated installation

echo "Validating dependencies..."
command -v python >/dev/null 2>&1 || { echo >&2 "Python is required for the installation of pyHDT! Aborting installation..."; exit 1; }
command -v pip >/dev/null 2>&1 || { echo >&2 "pip is required for the installation of pyHDT! Aborting installation..."; exit 1; }
command -v git >/dev/null 2>&1 || { echo >&2 "Git is required for the installation of pyHDT! Aborting installation..."; exit 1; }

echo "Fetching sources..."
git clone --recursive https://github.com/Callidon/pyHDT
cd pyHDT/

echo "Installing pybind11 mappings..."
pip install -r requirements.txt

echo "Installing pyHDT..."
python setup.py install
