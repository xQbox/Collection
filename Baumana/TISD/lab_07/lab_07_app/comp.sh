#!/bin/bash

echo "Введите абсолютный путь для первого файла: "
read file1
echo "Введите абсолютный путь для второго файла: "
read file2


# file1="./3.txt"
# file2="./4.txt"

# &> /dev/null добавляет вывод различий между файлами

if diff "$file1" "$file2" &> /dev/null; then
    echo "Files are the same"
else
    echo "Files are different"
fi