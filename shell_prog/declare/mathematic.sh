#!/bin/bash
a=100

declare -i c=$a/2
d=$(($a/2))
e=`expr $a / 2`

echo 'declare==> '$c
echo '(())==> '$d
echo 'expr==> '$e

g=2
h=3
if test $g -eq $h
then
	echo "equal"
fi

s1="abcd"
s2="abcd"
if test $s1 \> $s2
then 
	echo "they are same"
fi






