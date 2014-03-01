
#
# File:    sum1.pl
# Purpose: to sum the integers in the file sumit.dat
# Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
#
# Sat Oct 30 13:20:59 PDT 1999
#
# caveat - this is not nice code, copy at own risk ;)
#
# $Id: sumit.pl 326 2006-10-25 02:53:57Z laned $
#
#

	open (FP, "sumit.dat") || die "Could not open file sumit.dat\n";

	$sum = 0;

	while (<FP>)
	{
		chomp;
		$num = 0 + $_;
		$sum += $num if $num > 0;

	}
	print "The sum of the integers is $sum\n";

# eof


