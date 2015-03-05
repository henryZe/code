#!/bin/bash

if test $# = 0
then
	echo "number arguments required"
	exit
else
	if [ $# -gt 10 ]
	then 
		echo "only 10 arguments allowed"
	fi
fi

for args in $*
do
	count=`expr $args % 2`
	if [ $count -eq 1 ]
	then
		continue
	else
		output="$output $args"
	fi
done

echo "even numbers:$output"
