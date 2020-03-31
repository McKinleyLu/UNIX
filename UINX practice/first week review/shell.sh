#!/bin/bash
echo -e - n  "fist program"
skill=good
skillful=best
skillfully="not good but best"
echo "fist program test"${skill}${skillful}$skillfullywrong

echo  "second program"
echo  "please intput the name number expertise"
echo "shell name $0"
echo "name: $1"
echo "number $2"
echo "expertise $3"
echo "canshu:$*"
echo "number of canshu $#"
echo "shell_ID:$$"

echo "third program of function"
function func(){
echo "please input the two agruments"
echo "URL:$4"
echo "URL:$5"
}
echo "diaoyong hanshu func....."

echo "fourth program OF  max "
echo "please input the two agruments"
read a
read b
if (($a >= $b))
then 
     echo "max is :$a"
else
     echo "max is :$b"
fi

echo "five program CASE "
echo "please input the  agrument"
read c
case $c in
  [0-9])
	  printf "0-9";;
  [abc])  printf "$c";;
  *)      printf "i do not know"
esac

echo "sixth loop program of while"
i=1
sum=0
while((i<=10))
do
	((sum+=i))
	((++i))
done
echo -n "$sum/t"




