echo "No.1"
awk '{print $1,$5}' grade.txt

echo "No.2"
awk '{printf"%-10s:%-d\n",$1,$5}' grade.txt

echo "No.3"
awk '$5==11 && $6>=90{print $0}' grade.txt

echo "No.4"
awk 'NR==1 || $6>90{print}' grade.txt

echo "No.5"
awk 'BEGIN{FS=":"}{print $1}' /etc/passwd 
echo "No.5_1"
awk -F: '{print $1}' /etc/passwd 
echo "No.5_2"
awk -F'[\t;:]' '{print $1}' /etc/passwd 

echo "No.6"
awk '$0~/Brown.*/{print}' grade.txt

echo "No.7"
awk '$0!~/Brown.*/{print}' grade.txt

echo "No.8"
awk 'NR!=1 {print > $5}' grade.txt
echo "No.8_1"
awk 'NR!=1 {print $1,$6 > $5}' grade.txt

echo "No.9"
awk 'NR!=1 {if($4~/Brown.*|Black/) print > "high.txt";else if($4~/Yellow|[Gg]reen/) print > "middle.txt";else print > "low.txt"}' grade.txt

echo "No.10"
awk '{sum+=$6} END{print sum}' grade.txt

echo "No.11"
awk 'NR!=1 {a[$4]++;} END{for(i in a) print i","a[i];}' grade.txt


