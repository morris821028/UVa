
//
// File:    sumit.cpp
// Purpose: to sum the integers in the file sumit.dat
// Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
//
// caveat - this is not nice code, copy at own risk ;)
//
// $Id: sumit.cpp 1633 2008-11-05 03:29:46Z laned $
//
//

#include <fstream>
#include <iostream>
using namespace std;

main ()
{
	int num;
	int sum;
	ifstream filein("sumit.dat");

	if (filein.fail())
	{
		cerr << "Could not read from file sumit.dat " << endl;
	}
	else
	{

		sum = 0;

		while(!filein.eof())
		{
			filein >> num;

			if (num > 0)
			{
				sum += num;
			}
		}

		cout << "The sum of the integers is " << sum << endl;

	}
}

// eof 
