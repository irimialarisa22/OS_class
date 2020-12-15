#!/bin/bash
# Să se afișeze numărul de fișiere din linia de comanda a lui awk, numărul total de cuvinte și numărul mediu de cuvinte din fișiere.

read files
echo 'The number of files is: '
echo $files | wc -w
nrfiles=$(echo $files | wc -w)
words=0
echo 'Number of words '
awk '{for(i=1;i<=NF;i++) k++} END { printf k}' $files
echo '\n'
words=$(awk '{for(i=1;i<=NF;i++) k++} END {printf k}' $files)
echo 'Average words per file '
echo $(($words/$nrfiles))