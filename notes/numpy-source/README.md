# Notes:  `numpy` Source

The full `numpy` source code is [available on GitHub](https://github.com/numpy/numpy) and understanding it is a fun challenge.  I have been using the `numpy` source to learn more about BLAS and about how Python C Extensions are structured in the real world.

## Basic Structure

* `numpy/`
    - `core/`
        - `src/`
            - `multiarray/`
                - `arrayobject.c`
                - `calculuation.c`
                - `item_selection.c`
                - `iterators.c`
                - `mapping.c`
                - `methods.c`
                - `multiarraymodule.c`
                - `number.c`
                - `sequence.c`
                - `shape.c`
                - `vdot.c`
            - `npymath/`
            - `umath/`
        - `__init__.py`
        - `numeric.py`
        - `setup.py`
    - `distutils/`
    - `fft/`
    - `linalg/`
    - `ma/`
    - `random/`
