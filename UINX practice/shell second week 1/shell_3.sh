#!/bin/bash
account="1001"
password="1210"
if [ $# -ne 2 ]
then 
	echo "arguments not enough"
	exit -1
fi

#account=$1 password=$2
if [ $1 -eq $account -a $2 == $password ]
then
	echo "$1 and $2 is right"
else
	echo "wrong"
fi
