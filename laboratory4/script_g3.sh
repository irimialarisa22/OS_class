#!/bin/bash
# Să se afișeze numele tuturor fișierelor binare din directoarele date ca parametri linia de comandă și din subdirectoarele acestora.

mkdir A
touch file{1..5}.bin
cd A
mkdir B
touch subfile{6..10}.bin
cd .
for dir in $@; do
        find $dir2 | grep  ".*\.bin$"
done