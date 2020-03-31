#!/bin/bash
for file in *.txt
do
	delete=`basename $file .txt`
	mv $file $delete.doc
done
