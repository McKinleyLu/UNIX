#!/bin/bash
if [ $# -ne 1 ]
then
        echo "argument not right"
else
        user=$1
        if who | grep -q $user;
                then
                     echo $1"is  loggin"
             else
                     echo $1"is not  loggin"
             fi
fi

