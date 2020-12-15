#!/bin/bash
# Să se scrie un program Shell care, începând din directorul dat ca parametru, în jos, face o lista a tuturor numelor care 
#apar (fișiere și directoare), și pentru fiecare nume de fișier afișează numărul maxim al liniilor care se repetă (în același fișier).

dir=$1
ls -R $dir
for file in `find ./$dir -type f`; do
number=`sort $file | uniq -c | grep -v '^ *1 '`
echo ${file##*/} ' ' $number
done