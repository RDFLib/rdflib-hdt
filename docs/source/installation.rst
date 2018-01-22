Installation
=============

Requirements
^^^^^^^^^^^^

* `git <https://git-scm.com/>`_
* `pip <https://pip.pypa.io/en/stable/>`_
* **gcc/clang** with **c++11 support**
* **Python Development headers**

You must have the `Python.h` header available on your system.
For example, for Python 3.4, install the `python3.4-dev` package on Debian/Ubuntu systems.

Installation using Git
^^^^^^^^^^^^^^^^^^^^^^

Installation in a `virtualenv <https://virtualenv.pypa.io/en/stable/>`_ is strongly advised!

.. code-block:: bash

  git clone --recursive https://github.com/Callidon/pyHDT
  cd pyHDT/
  pip install -r requirements.txt
  python setup.py install
