#!/bin/bash

TMPOUT=tmp.out

for f in *.in
do
	tmp=${f%%.in}
	echo -n "testcase - $tmp"
	time ./main2 <${tmp}.in >$TMPOUT
	diff -w ${tmp}.out $TMPOUT
done

