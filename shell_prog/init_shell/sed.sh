#!/bin/sh

echo "No.1"
sed "s/-year/years/" people.txt


echo "No.2"
sed "2s/-year/years/" people.txt

echo "No.2_1"
sed "2,5s/-year/years/" people.txt

echo "No.3"
sed -i "2s/-year/years/" people.txt

echo "No.4"
sed "s/s/S/g" people.txt

echo "No.5"
sed "s/s/S/2" people.txt

echo "No.6"
sed "s/s/S/2g" people.txt

echo "No.7"
sed 's/-year/year/;3,$s/.$//' people.txt

echo "No.7_1"
sed -e 's/-year/years/' -e'3,$s/.$//' people.txt

echo "No.8"
sed "s/is/[&]/" people.txt

echo "No.9"
sed "s/\(^.*\)\tis.*from \(.*\)./\1\t:\2/g" people.txt

echo "No.10"
sed 'N;s/is/IS/' people.txt

echo "No.11"
sed '3i abcd' people.txt
echo "No.11_1"
sed '2a abcd' people.txt
echo "No.11_2"
sed '1,4a abcd' people.txt
echo "No.11_3"
sed '/US/a abcd' people.txt

echo "No.12"
sed "2c ok" people.txt

echo "No.13"
sed '2d' people.txt
echo "No.13_1"
sed '/US/d' people.txt
echo "No.13_2"
sed '/\<he\>/d' people.txt

echo "No.14"
sed '/Chen/p' people.txt -n
echo "No.14_1"
sed '/Chen/,/Michael/p' people.txt -n
echo "No.14_2"
sed '3,/UK/p' people.txt -n
echo "No.14_3"
sed '/UK/,6p' people.txt -n
echo "No.14_4"
sed '/UK/,3p' people.txt -n
echo "No.14_5"
sed '5,/US/p' people.txt -n

echo "No.15"
sed "/US/,+2p" people.txt -n

echo "No.16"
sed '{/\<he\>/{/18/p}}' people.txt -n


