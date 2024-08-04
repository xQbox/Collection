#!/bin/bash
cd ../..

count=0

RED='\033[91m'
NC='\033[0m'
GREEN='\033[92m'

for input_file in ./func_tests/data/pos_[0-9][0-9]_in.txt; do
	number=$(echo "$input_file" | grep -o "[0-9]*")
	expected=$(echo | find ./func_tests/data -name "pos_$number\_out.txt")

	./func_tests/scripts/pos_case.sh "$input_file" "$expected"
	result=$?

	file_name="POS_$number ->"	
	
	if [[ $result -eq 0 ]]; then
		printf "$file_name ${GREEN}PASSED${NC}\n"
	else
		printf "$file_name ${RED}FAILED${NC}\n"
		count=$((count+1))
	fi		
done

echo

for input_file in ./func_tests/data/neg_[0-9][0-9]_in.txt; do
	number=$(echo "$input_file" | grep -o "[0-9]*")

	./func_tests/scripts/neg_case.sh "$input_file"
	result=$?
		
	file_name="NEG_$number ->"
	
	if [[ $result == 0 ]]; then
		printf "$file_name ${GREEN}PASSED${NC}\n"
	else
		printf "$file_name ${RED}FAILED${NC}\n"
		count=$((count+1))
	fi
done

echo
echo "Failed:" "$count"
exit $count
