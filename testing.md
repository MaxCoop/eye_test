# Continuous Integration Pipeline

In order to make our software pipeline and code more robust we use the following tests and tools.

## Python

All our python code is validated using `Pylint` prior to being committed to the repo.
Once a commit is made we use Travis CI to automatically run all unit tests against our new release.
For website tests we use `Selenium`, and `Doctest`

## C++ - none of the following has been done yet

We check all our C++ code with either `cpplint` [Google style guide] or `cppcheck` [`sudo apt get install cppcheck`]
Once a commit is made we use Travis CI to automatically run all unit tests against our new release.
