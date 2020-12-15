#!/bin/bash
# Să se șteargă toate cuvintele care conțin cel puțin o cifră din fișierele date ca parametri.

for file in $@; do # $@ takes all the parameters from the console
        sed -r 's/\b[A-Za-z]*[0-9]+[A-Za-z]*\b//g' $file
done