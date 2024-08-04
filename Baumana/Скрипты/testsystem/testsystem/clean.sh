#!/bin/bash

rm -f ./*.exe ./*.o ./*.gcda ./*.c.gcov ./*.gcov ./*.gcno
cd ./func_tests/scripts/ || return
rm -f ./*.txt ./*.gcov
