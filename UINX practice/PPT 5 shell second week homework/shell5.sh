#!/bin/bash
echo "                  welcome to program            "
echo "                  program is loading...         "
sleep 2
echo "                  1.calculate                   "
echo "                  2.file or direvtion exsit     "
echo "                  3.string whether equal        "
echo "                  4.exit                        "
for((;;))
do
    read  -p "please input your order" order   
    case "$order" in
	"1")    echo "please input number1 and number2 and op"
		read number1
		read number2
		read op 
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

      ;;		
	"2") read -p "please input the file/direction's name" filename
		if [ -f  $filename  -o  -d $filename ]
		then
			echo " exist"
		else
			echo " not exsist"
		fi
		;;
	"3")  read -p "please input the first string"str1
	      read -p "please input the second string"str2
	      if [ "$str1" = "$str2" ]
	      then
		      echo "equal"
	      else
		      echo "different"
	      fi
	      ;;
      "4")  echo "the program is over..." 
	    sleep 2
	    break;; 
	  *)  echo "you input a wrong order,please input again";;  
   esac 
 done
 






