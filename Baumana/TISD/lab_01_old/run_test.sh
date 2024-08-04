#!/bin/bash 

declare -i COUNT_OK=0
declare -i COUNT_FAILED=0

function run_test() {
	PROGRAM_EXECUTABLE=cat
	IN_FILE_NAME=$(basename "$1")
	OUT_FILE_NAME=${IN_FILE_NAME/in/out}
	ARGS_FILE_NAME=${IN_FILE_NAME/in/args}
	# echo "$1" "$IN_FILE_NAME" "$OUT_FILE_NAME" "$ARGS_FILE_NAME"

	if [ ! -f "$OUT_FILE_NAME" ]; then
#		echo "Missing out file: $IN_FILE_NAME"
		return
	fi

	if [ -f "$ARGS_FILE_NAME" ]; then
#		echo "Missing out file: $IN_FILE_NAME"
		TEST_ARGS=$(cat "$ARGS_FILE_NAME")
	else
		TEST_ARGS=
	fi
	
	echo "Running test: $IN_FILE_NAME (args=$TEST_ARGS)"
	cat "$IN_FILE_NAME" | "$PROGRAM_EXECUTABLE" $TEST_ARGS | diff "$OUT_FILE_NAME" - &>/dev/null
	if [ $? -eq 0 ]
	then
		echo "OK"
		COUNT_OK=$COUNT_OK+1
	else
		echo "FAILED"
		COUNT_FAILED=$COUNT_FAILED+1
	fi

}

# export -f run_test
# find . -regex '.*/pos_.*_in.txt' -exec bash -c "run_test \"{}\"" \;

for f in pos_*_in.txt; do
	run_test "$f"
done

echo "OK=$COUNT_OK"
echo "FAILED=$COUNT_FAILED"
