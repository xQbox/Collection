#!/bin/bash

input_file=$1
expected_output=$2
temp_output="./func_tests/data/temp.txt"
app="./app.exe"

result=0

if [[ "$#" -gt 1 ]]; then
	query="$app "
	query+=" < $input_file"
	query+=" > $temp_output"

	eval $query
	
	if [[ "$?" != 0 ]]; then
		exit 1
	else
		tail -1 $temp_output > temp_tail.txt
		./func_tests/scripts/comparator.sh "temp_tail.txt" "$expected_output"
		result=$?
	fi

else
	exit 3
fi

exit "$result"
