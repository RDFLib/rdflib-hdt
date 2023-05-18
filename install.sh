#!/usr/bin/env bash
# scripts for automated installation

echo "Validating dependencies..."
command -v python >/dev/null 2>&1 || { echo >&2 "Python is required for the installation of rdflib_hdt! Aborting installation..."; exit 1; }
command -v pip >/dev/null 2>&1 || { echo >&2 "pip is required for the installation of rdflib_hdt! Aborting installation..."; exit 1; }
command -v curl >/dev/null 2>&1 || { echo >&2 "curl is required for the installation of rdflib_hdt! Aborting installation..."; exit 1; }
command -v unzip >/dev/null 2>&1 || { echo >&2 "unzip is required for the installation of rdflib_hdt! Aborting installation..."; exit 1; }

echo "Installing dependencies..."
pipenv install

echo "Installing pyHDT..."
pipenv run python setup.py install
