#!/bin/bash
#Name: Kenneth Omo
#Serial Number: 23
#CS 4350-Unix Systems Programming
#Assignment Number: 2
#Due Date: 2/24/2020

#Password Number 5 on Assignment
while :
do
  read -p "Please enter a Password: " pass
  #pass=11111111111111
  CORRECTLENGTH=8
  length=${#pass} #the length of the password input

  if [ $length -lt $CORRECTLENGTH ]; then
    echo "length not correct"
  elif ! [[ $pass =~ [0-9] ]]; then
    echo "does not contain a number"
  elif ! [[ $pass =~ [A-Z] ]]; then
    echo "does not contain a captail letter"
  else
    echo "Strong Password Accepted!"
    break
  fi
done
echo "Complete"




exit 0
