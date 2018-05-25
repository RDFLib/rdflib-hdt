Installation
=============

Requirements
^^^^^^^^^^^^

* `pip <https://pip.pypa.io/en/stable/>`_
* **gcc/clang** with **c++11 support**
* **Python Development headers**

You must have the `Python.h` header available on your system.
For example, for Python 3.4, install the `python3.4-dev` package on Debian/Ubuntu systems.

Then, install the `pybind11
library <http://pybind11.readthedocs.io/en/stable/>`__

::

    pip install pybind11

Installation
^^^^^^^^^^^^^

Installation in a `virtualenv <https://virtualenv.pypa.io/en/stable/>`_ is **strongly advised!**

Installation with pip
-------------------------

::

    pip install hdt


Manual installation
-------------------------

.. code-block:: bash

  git clone --recursive https://github.com/Callidon/pyHDT
  cd pyHDT/
  pip install -r requirements.txt
  python setup.py install
