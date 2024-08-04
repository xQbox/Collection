#!/bin/bash
if diff "file1.txt" "bfile.txt" ; then
	echo "Equals"
else 
	echo "Different"
fi
