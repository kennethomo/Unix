#!/bin/bash

choice=abcd
#echo $choice | rev
length=${#choice}
taco=""

for (( i=$length - 1; i >= 0; i-- )); do
  taco="$taco${choice:$i:1}"
done
echo $taco


exit 0
