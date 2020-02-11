#!/bin/bash

choice=abcd
#echo $choice | rev
length=${#choice}

for (( i = $length - 1; i >= 0; i-- )); do
  reverse = "$reverse${choice:$i:1}"
done
echo $reverse


exit 0
