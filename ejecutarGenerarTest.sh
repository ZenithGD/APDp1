#!/bin/bash

echo "Ejecutando generateTest............."
./bin/main -g

path="testfiles/generated"
for file in $(ls $path)
do
    echo "Testing file '$file' -----------------"
    echo "Count"
    ./bin/main -e "$path/$file" --count || exit 1
    echo "Quick"
    ./bin/main -e "$path/$file" --quick || exit 1
    echo "Radix"
    ./bin/main -e "$path/$file" --radix || exit 1
    echo "--------------------------------------------------"
done
