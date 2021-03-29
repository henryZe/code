#! /bin/sh 

ls | wc -w

ls [^0-9]*.c

read -p "pls input Num:" a b
echo 'hello $a $b'
echo "hello $a $b `ls`"

cat file && echo "success"
cat bull || echo "fail"

cp file1 file.bk || touch file1
