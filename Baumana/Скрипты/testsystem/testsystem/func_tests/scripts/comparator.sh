#!/bin/bash

file1=$1
file2=$2

if [ "$3" == "-v" ]; then
    verbose=true
fi

if ! [ -e $1 ]; then
    if [ $verbose ]; then
        echo "Файлa $1 не существует"
    else
        echo 1
    fi
    exit 1
fi

if ! [ -e $2 ]; then
    if [ $verbose ]; then
        echo "Файлa $2 не существует"
    else
        echo 1
    fi
    exit 1
fi

text1=$(cat "$file1")
text2=$(cat "$file2")

if ! [ $verbose ]; then
    if [ "$text1" == "$text2" ]; then
        exit 0
    else
       exit 1
    fi
else
    len1="${#text1}"
    len2="${#text2}"
    echo "lens: $len1 and $len2"
    if [ "$len1" != "$len2" ]; then
        echo "Фрагменты имеют разные длины: $len1 != $len2"
        exit 1
    else
        if [ "$text1" == "$text2" ]; then
            echo "Фрагменты совпадают"
            exit 0
        else
            echo "Фрагменты не совпадают"
            exit 1
        fi
    fi
fi
