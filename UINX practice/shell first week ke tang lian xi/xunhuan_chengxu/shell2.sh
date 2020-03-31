#/bin/bash
i=10
max=-9999
while ((i>=1))
do
	read a
        if [ $a -gt $max ]
	then 
		((max=a))
	fi
	((--i))
done
echo "The max_number is $max"
