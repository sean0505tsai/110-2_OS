#! /bin/sh

echo 'The content of file2.txt: '
cat file2.txt

echo ''
echo 'The content of file1.txt: '
cat file1.txt

rm file1.txt
ls

strace rm file2.txt
