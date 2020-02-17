#!/bin/bash
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
