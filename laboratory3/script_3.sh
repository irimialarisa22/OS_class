#!/bin/bash
#Să se scrie un script shell care primește ca parametru un nume de utilizator. Să se determine numele întreg al acelui utilizator și dacă el/ea este conectat(a) la sistem.

name="$1"
user=`grep $name passwd.fake | cut -d : -f 5`
echo $user
logged=`grep $name who.fake | grep -c $name`
echo $logged
if [ $logged == 1 ]; then
        echo 'User' $name 'is logged in system'
fi