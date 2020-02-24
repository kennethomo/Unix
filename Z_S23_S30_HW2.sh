#!/bin/bash

#Name: Kenneth Omo, James Steckler
#Serial Number: 23, 30
#CS 4350-Unix Systems Programming
#Assignment Number: 2
#Due Date: 2/24/2020

# This shell script does a variety of tasks with no user input from the
# the terminal, and only a command line parameter.  It is compatible
# in a variety of shell and bash environments and has been tested on the
# Zeus and Eros Linux servers for TX State.

# The main six tasks this script accomplishes are the following:
#   1. Determines if current user is the root user or not
#   2. Displays the number of files and subdirectories for the command line
#      paramter
#   3. Displays the number of .txt files for the command line parameter
#   4. Creates and dsiplays a file with the names of empty sub folders
#   5. Determines if the command line paramter would qualify for a password
#      by checking length, capitalization, and alphanumeric presence
#   6. Displays the reversed command line paramater

#############################################################################
# README:    $ chmod a+x Z_S23_S30_HW2.sh
#            $ ./Z_S23_S30_HW2.sh [Variable]
# Please note [Variable], should not include brackets, and should be a name
# of an existing directory for clear results.
#############################################################################

input=$1 #Global Varaible to take 1st command line argument

#############################################################################
# 1. UserIDCheck()
#
# This function utilizes the default UID variable in shell/bash to compare
# to the default root user ID to determine if the current user is root
# authorized, or not a current root user.
#############################################################################
UserIDCheck(){
  root=501

  if ! [[ $UID =~ $root ]]; then
  	echo "You are not the root user."
  else
  	echo "You are the root user."
  fi
}

#############################################################################
# 2. CountFiles()
#
# This function counts the number of files and directories given from
# the command line argument
#############################################################################
CountFiles(){
file=0
dirs=0

DIR=$input
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
  echo "Directory does not exist."
fi

echo "Number of Files: $file"
echo "Number of Directories: $dirs"
}

#############################################################################
# 3. CountTXTFiles()
#
# Will count all xxxx.txt files in the provided directory and display the
# count to the terminal
#############################################################################
CountTXTFiles(){
  filenumber=0
  #count=$(find $input -maxdepth 1 -type f -name '*.txt' | wc -l)
  cd $input || echo "Directory does not exist"
  for file in *.txt
  do
    let filenumber=$filenumber+1
      #if ! [ -d "$d" ]; then
      #    if [[ $d == *.txt ]]; then
     #       fileNumber=$((files+1))
    #      fi
   #   fi
  done
  cd ..
  echo "Number of .txt files: $filenumber"
}
#############################################################################
# 4. SubFolders()
#
# Will create a list of all empty subfolder names in the command line
# directory, and then add those names into a new file
#############################################################################
#Number 4 on Assignment
SubFolders(){
  find $input -maxdepth 1 -type d -empty > s23s30outputfile
  echo "List of all empty subfolders:"
  cat s23s30outputfile
}

#############################################################################
# 6. Password()
#
# Takes the command line argument and tests whether it is length 8,
# uses numbers, and has both capital and lowercase letters, and notifies of
# weak or acceptable passwords
#############################################################################
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

#############################################################################
# 6. ReverseDir()
#
# This function takes the command line argument and displays it's string
# in reverse order.
#############################################################################
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
# Program Execution below this line
echo
echo "Opportunities to program scripts in UNIX"
echo
echo "1: Determining if you are root user."
UserIDCheck
echo
echo "2: Counting all files and folders."
CountFiles
echo
echo "3: Counting all .txt files."
CountTXTFiles
echo
echo "4: Creating a file of empty subfolders and displaying contents."
SubFolders
echo
echo "5: Testing password strength."
Password
echo
echo "6: Reversing string."
ReverseDir
echo
echo "Implemented by Kenneth Omo and James Steckler - 2-24-2020"

exit 0
