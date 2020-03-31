#!/bin/bash
user=$1
while true
do
        if who | grep -q $user;
                then
                     echo $1"is  loggin"
             else
                     echo $1"is not  loggin"
             fi


sleep 1
done
