#!/bin/bash
#User ID check

root=501

if ! [[ $UID =~ $root ]]; then
	echo "You are not the root user"
else
	echo "You are the root user"
fi

  
