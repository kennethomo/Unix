#!/bin/bash


ReverseDir(){
  choice=$1
  #echo $choice | rev #This could also work!
  local length=${#choice}
  taco=""

  for (( i=$length - 1; i >= 0; i-- )); do
    taco="$taco${choice:$i:1}"
  done
  echo $taco
}

ReverseDir

exit 0
