#!/bin/bash
# Să se scrie un script shell care va redenumi toate fișierele ".txt" din directorul curent și din toate subdirectoarele acestuia, dându-le extensia ".ascii".

touch file{1..5}.txt
mkdir subDir
cd subDir
touch subfile{6..10}.txt
cd ..
echo 'The files have been created successfully'
echo 'Would you like to rename the files with the .ascii extension? y/n'
read k
if [ $k  == "y" ]; then
        for file in $(find . -name "*.txt"); do
                mv ${file} ${file%.txt}.ascii
        done
        echo 'The files have been renamed successfully'
fi