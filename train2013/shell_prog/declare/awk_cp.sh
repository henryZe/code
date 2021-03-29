#!/bin/bash

addr=`grep "awk" $1 -rHwn --exclude-dir=*/awks | awk 'BEGIN{FS=":"} {print $1}'|uniq`

if [ ! -d "awks" ]
then
	`mkdir awks`
fi

for file in $addr
do
	echo $file > temp
	name=`sed 's/\//_/g;s/^\.\._//g' temp`
	echo "$name"
	`cp $file ./awks/$name`
done
