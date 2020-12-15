#!/bin/bash
# Să se scrie un program Shell care, începând din directorul dat ca parametru, în jos, face o lista a tuturor numelor care apar
# (fișiere și directoare), și pentru fiecare nume de fișier afișează numărul fișierelor cu același nume.

dir=$1
ls -R $dir
for file in `find ./$dir -type f`; do
numfile=`ls $file* | wc -l`
# ${file##*/} takes only the filename from a path
echo ${file##*/} ' ' $numfile
done