#!/bin/bash

read -p "Please input name:" name
who=`who|awk '{print $1}'|uniq`
quit="quit"
flag=0

until [ $name = $quit ]
do
	for list in $who
	do
		if [ $name = $list ]
		then
			echo "$name is online"
			flag=1
			break
		fi
	done
	if [ $flag -eq 0 ]
	then
		echo "$name is NOT online"
	fi

flag=0
read -p "Please input name:" name

done
