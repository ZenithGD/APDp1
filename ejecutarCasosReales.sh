#!/bin/bash

# Run tests for all files in test folder

if [ $# -lt 1 ]
then
    echo "Usage : ./ejecutarCasosReales <folder>"
    exit 1
fi

path=$1

for file in $(ls $1)
do
    echo "Testing file '$file' ---------------"
    echo "Count"
    ./bin/main -e "$path/$file" --count || exit 1
    echo "Quick"
    ./bin/main -e "$path/$file" --quick || exit 1
    echo "Radix"
    ./bin/main -e "$path/$file" --radix || exit 1
    echo "--------------------------------------------------"
done