#! /bin/sh

echo 'The content of file1.txt: '
cat file1.txt

echo ''
echo 'The inode number of file1.txt: '
ls -li file1.txt

echo ''
echo 'Create a hard link between file1.txt and file2.txt.'
ln file1.txt file2.txt

echo ''
echo 'The inode number of file2.txt: '
ls -li file2.txt

echo ''
echo 'The content of file2.txt: '
cat file2.txt
