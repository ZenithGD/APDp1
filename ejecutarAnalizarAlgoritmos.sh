#!/bin/bash

echo "Testing '--radix'"
./bin/main -a --radix
python3 plotgraphs.py radixAnalysis.csv

echo "Testing '--count'"
./bin/main -a --count
python3 plotgraphs.py countAnalysis.csv

echo "Testing '--quick'"
./bin/main -a --quick
python3 plotgraphs.py quicksortAnalysis.csv
   