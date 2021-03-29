#!/bin/bash

func()
{
	echo "hello"
	echo "\$S1:$1"
	echo "\$S2:$2"
	b="ok"
	declare c="false"
}

echo "a"

S1="xyz"
S2="zyx"
func $S1 $S2

echo "b"
echo $b
echo $c
