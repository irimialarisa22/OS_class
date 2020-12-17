#!/bin/sh
if [ ! -d $1 ]
then echo "-1"
exit 1
fi
echo `find $1 -maxdepth 1 -iname '*.txt'` | cat
