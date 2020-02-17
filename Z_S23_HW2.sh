#!/bin/bash
#Name: Kenneth Omo
#Serial Number: 23
#CS 4350-Unix Systems Programming
#Assignment Number: 2
#Due Date: 2/24/2020

#Number 2 on Assignment
#CountFiles(){

DIR=$1
cd "$DIR" || exit
files=0
dirs=0

for d in *;
do
    if [ -d "$d" ]; then
        dirs=$((dirs+1))
    else
        file=$((file+1))
    fi
done
echo "Files $file"
echo "Directories $dirs"
#}

#Password Number 5 on Assignment
pass=$1
CORRECTLENGTH=8
length=${#pass} #the length of the password input

if [ $length -lt $CORRECTLENGTH ]; then
  echo "Weak Password"
elif ! [[ $pass =~ [0-9] ]]; then
  echo "Weak Password"
elif ! [[ $pass =~ [A-Za-z] ]]; then
  echo "Weak Password"
else
  echo "Strong Password Accepted!"
  break
fi

#Number 6 on Assignment
choice=$1
#echo $choice | rev #This could also work!
length=${#choice}
taco=""

for (( i=$length - 1; i >= 0; i-- )); do
  taco="$taco${choice:$i:1}"
done
echo $taco




exit 0
