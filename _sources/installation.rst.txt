Installation
=============

Requirements
^^^^^^^^^^^^

* Python *version 3.6.4 or higher*
* `pip <https://pip.pypa.io/en/stable/>`_
* **gcc/clang** with **c++11 support**
* **Python Development headers**

.. note::
  You must have the `Python.h` header available on your system.
  For example, for Python 3.4, install the `python3.4-dev` package on Debian/Ubuntu systems.

Installation
^^^^^^^^^^^^^

Installation using `pipenv <https://github.com/pypa/pipenv>`_ or a `virtualenv <https://virtualenv.pypa.io/en/stable/>`_ is **strongly advised!**

PyPi installation (recommended)
-------------------------------

.. code-block:: bash

   # you can install using pip
   pip install rdflib-hdt

   # or you can use pipenv
   pipenv install rdflib-hdt

Manual installation
-------------------

**Requirement:** `pipenv <https://github.com/pypa/pipenv>`_ 

.. code-block:: bash

   git clone https://github.com/Callidon/pyHDT
   cd pyHDT/
   ./install.sh
