#!/bin/bash

input_file=$1
temp_output="./func_tests/data/temp.txt"
app="./app.exe"

if [[ "$#" -eq 1 ]]; then
	query="$app "
	query+=" < $input_file"
	query+=" > $temp_output"

	eval $query
	
    if [[ "$?" != 0 ]]; then
	result=0
    else
	result=1
    fi
else
    exit 2
fi

exit "$result"
