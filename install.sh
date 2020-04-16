#!/usr/bin/env bash
# scripts for automated installation

echo "Validating dependencies..."
command -v python >/dev/null 2>&1 || { echo >&2 "Python is required for the installation of rdflib_hdt! Aborting installation..."; exit 1; }
command -v pip >/dev/null 2>&1 || { echo >&2 "pip is required for the installation of rdflib_hdt! Aborting installation..."; exit 1; }
command -v curl >/dev/null 2>&1 || { echo >&2 "curl is required for the installation of rdflib_hdt! Aborting installation..."; exit 1; }
command -v unzip >/dev/null 2>&1 || { echo >&2 "unzip is required for the installation of rdflib_hdt! Aborting installation..."; exit 1; }

echo "Downloading HDT..."
curl -LO https://github.com/rdfhdt/hdt-cpp/archive/v1.3.3.zip
unzip -qq v1.3.3.zip

echo "Installing dependencies..."
pipenv install

echo "Installing pyHDT..."
pipenv run python setup.py install

echo "Cleaning up..."
rm v1.3.3.zip
rm -rf hdt-cpp-1.3.3/
