#!/bin/bash
if [ $# -ne 1 ]
then
	echo "Usage $0 file-name"
	exit -1
fi 

if [ -f $1 ]
then 
	echo "$1 is a file"
elif [ -d $1 ]
then
	echo "$1 is a direction"
	cd $1
	ls -l
else
	echo "no"
fi
