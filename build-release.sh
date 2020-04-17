#!/usr/bin/env bash
# scripts for automated release

echo "Validating dependencies..."
command -v python >/dev/null 2>&1 || { echo >&2 "Python is required for building a release of rdflib_hdt! Aborting script..."; exit 1; }
command -v pipenv >/dev/null 2>&1 || { echo >&2 "pipenv is required for building a release of rdflib_hdt! Aborting script..."; exit 1; }
command -v curl >/dev/null 2>&1 || { echo >&2 "curl is required for building a release of rdflib_hdt! Aborting script..."; exit 1; }
command -v unzip >/dev/null 2>&1 || { echo >&2 "unzip is required for building a release of rdflib_hdt! Aborting script..."; exit 1; }

echo "Downloading HDT..."
curl -LO https://github.com/rdfhdt/hdt-cpp/archive/v1.3.3.zip
unzip -qq v1.3.3.zip

echo "Building PyPi release in dist/..."
pipenv run python setup.py sdist

echo "Cleaning up..."
rm v1.3.3.zip
rm -rf hdt-cpp-1.3.3/
