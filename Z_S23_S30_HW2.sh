#!/bin/bash
#Name: Kenneth Omo
#Serial Number: 23
#CS 4350-Unix Systems Programming
#Assignment Number: 2
#Due Date: 2/24/2020

input=$1 #Global Varaible

#User ID check Number 1 on Assignment
UserIDCheck(){
  root=501

  if ! [[ $UID =~ $root ]]; then
  	echo "You are not the root user"
  else
  	echo "You are the root user"
  fi
}

#Number 2 on Assignment
CountFiles(){
file=0
dirs=0

DIR=$input #input from terminal
if [[ -d "$DIR" ]]; then
  cd "$DIR"
  for d in *;
  do
      if [ -d "$d" ]; then
          dirs=$((dirs+1))
      else
          file=$((file+1))
      fi
  done
  cd ..
else
  echo "Directory does not exist"
fi

echo "Files $file"
echo "Directories $dirs"
}
#Number 3 on Assignment
CountTXTFiles(){
  fileNumber=0
  for d in *;
  do
      if ! [ -d "$d" ]; then
          if [[ $d == *.txt ]]; then
            fileNumber=$((file+1))
          fi
      fi
  done
  echo "Number of .txt files $fileNumber"
}
#Number 4 on Assignment
SubFolders(){
  find -type d -empty > file
  echo "List of all empty subfolders"
  cat file
}

#Password Number 5 on Assignment
Password(){
  pass=$input
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
}

#Number 6 on Assignment
ReverseDir(){
  choice=$input
  #echo $choice | rev #This could also work!
  length=${#choice}
  local reverse=""

  for (( i=$length - 1; i >= 0; i-- )); do
    reverse="$reverse${choice:$i:1}"
  done
  echo $reverse
}

echo "Opportunities to program scripts in UNIX"
echo

echo "1:"
UserIDCheck
echo "2:"
CountFiles
echo "3:"
CountTXTFiles
echo "4:"
SubFolders
echo "5:"
Password
echo "6:"
ReverseDir

echo
echo "Implemented by Kenneth Omo and James - 2-24-2020"


exit 0
