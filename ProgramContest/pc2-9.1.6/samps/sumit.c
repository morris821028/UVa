
/*
 * File:    sum.c
 * Purpose: to sum the integers in the file sumit.dat
 * Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
 *
 * Tue Oct 19 21:32:14 PDT 1999
 *
 * caveat - this is not nice code, copy at own risk ;)
 *
 * $Id: sumit.c 1633 2008-11-05 03:29:46Z laned $
 *
 */

#include <stdio.h>

#define INFILENAME "sumit.dat"

int main (int argc, char **argv)
{
	FILE *fp = fopen (INFILENAME,"r");
	int sum = 0;
	int i;

	if (fp)
	{
		while (1==fscanf(fp, "%d", &i))
		{
			sum += i > 0 ? i : 0;
		}
		fclose (fp);
		printf("The sum of the integers is %d \n",sum);
	}
	else
	{
		printf("Could not read from file sumit.dat \n");
		return(22);
	}

	return(0);
}

/* eof */
