#!/bin/bash

a="file.txt"

if test -e $a
then
	echo "exist "$a
	
else
	touch $a
fi


read -p "Input number:" n
case $n in
"1")
	echo "one"
	;;
"2")
	echo "two"
	;;
*)
	echo "unknown"
	;;
esac


filenames=`ls`
for file in $filenames
do 
	echo $file
done


var=0
while [ $var -le 100 ]
do
	sum=$(($sum+$var))	
	var=$(($var+1))
done
echo "while sum:$sum"


var=0
sum=0
until [ $var -gt 100 ]
do
	sum=$(($sum+$var))
	var=$(($var+1))
done
echo "until sum:$sum"




