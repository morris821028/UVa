
#include <stdio.h>
#include <stdlib.h>

/*
 * File:    practice.c
 * Purpose: sum of positive integers practice problem
 * Author:  pc2@ecs.csus.edu
 *
 * Returns 4 if there is an error, 0 on successful solution.
 *
 * $Id: practice.c 543 2007-05-03 18:32:47Z laned $
 */

#define INFILE "practice.in"

int main (int argc, char **argv)
{
	int sum = 0;
	int i = 0;
	FILE *fp = fopen (INFILE,  "rt");
	char line[128];

	if (fp != NULL)
	{
		while ( fgets (line, sizeof(line), fp) != NULL)
		{
			long inval = atol (line);
			sum = 0;

			if (inval == 0)
				exit (0);

			if (inval < 1)
			{
				for (i = 1; i >= inval; i --)
				       sum += i;	
			}
			else
			{
				for (i = 1; i <= inval; i ++)
				       sum += i;	
			}
			printf("N = %-3d    Sum = %d\n", inval, sum);
		}

		printf("Did not find trailing zero \n");

	}
	else
	{
		fprintf(stderr,"Could not read file %s \n", INFILE);
	}

	exit (4);
}

/* eof practice.c */
