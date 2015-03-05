#!/bin/bash

filenum=`ls`
num=0

for count in $filenum
do 
	num=$(($num+1))
done

echo $num
