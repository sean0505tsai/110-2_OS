#! /bin/sh

echo 'Create a soft link between file3.txt and file4.txt.'
ln -s file3.txt file4.txt

echo 'The inode number of file3.txt: '
ls -li file3.txt

echo ''
echo 'The inode number of file4.txt: '
ls -li file4.txt

echo ''
echo 'Edit file4.txt'
vim file4.txt

echo ''
echo 'The content of file3.txt: '
cat file3.txt

echo ''
echo 'The content of file4.txt: '
cat file4.txt

echo ''
echo 'Remove file3.txt'
rm file3.txt
ls

echo ''
echo 'Edit file4.txt'
vim file4.txt
ls
