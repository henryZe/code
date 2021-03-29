#!/bin/bash

name=`grep "awk" $1 -rHwn|awk 'BEGIN{FS=":"}{print $1}'|uniq`
echo $name

if [ ! -d "awks" ]
then
	`mkdir awks`
fi

for file in $name
do
	echo $file > files
	file_name=`awk 'BEGIN{FS="/"} {print $NF}' files`

	if [ -e awks/$file_name ]
	then
		n=`ls awks/$file_name*|wc -w`
		`cp $file ./awks/$file_name$n`
	else
		`cp $file ./awks`	
	fi
done
