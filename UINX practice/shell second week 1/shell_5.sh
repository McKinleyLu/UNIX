#!/bin/bash
read -p "please input n" n
for i in `seq 1 9`
do
        result=$((i*n))
        echo -n  $result
done

m=1
while [ $m -le 10 ]
do
        reslut=$(($m*$n))
        echo -n  $result
        m = ((m+1))
done

