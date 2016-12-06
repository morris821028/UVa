#!/bin/bash

TMPOUT=tmp.out

for f in *.in
do
	tmp=${f%%.in}
	echo -n "testcase - $tmp"
	time ./main <${tmp}.in >$TMPOUT
	diff -w ${tmp}.out $TMPOUT
done

rm $TMPOUT
