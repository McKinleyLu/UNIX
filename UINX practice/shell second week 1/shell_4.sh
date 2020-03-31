#!/bin/bash
read -p "please input first number"    number1
read -p "please input second number"   number2
read -p "please input third (+ - * /)" op

#echo $number1
#echo $number2
#echo "$op"

#检验非空
if [ -n $number1 -a -n $number2 -a -n "$op" ]
then
    if [ "$op" == "+" ]
    then 
	    result=$((number1+number2))
    elif [ "$op" == "-" ] 
    then
	    result=$((number1-number2))
    elif [ "$op" == "*" ]
    then
        result=$((number1*number2))
    elif [ "$op" == "/" ]
    then
	    result=$((number1/number2))
    fi
            echo $result    
else
	echo "some numbers or operator must  be empty or "$op" is wrong"
	exit -1
fi

  case "$op" in
    "+")
	    result=$((number1+number2)) ;;
    "-") 
            result=$((number1-number2)) ;;
    "*")
            result=$((number1*number2)) ;;
    "/")
             result=$((number1/number2)) ;;
     *)            echo "wrong op"
     esac
     echo $result

