
//
// File:    isumit.cpp
// Purpose: to sum the integers from stdin
// Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
//
// $Id: isumit.cpp 1111 2007-11-28 22:14:52Z boudreat $
//
//

#include <fstream>
#include <iostream>
using namespace std;

main ()
{
	int num;
	int sum;

		sum = 0;

	cin >> num;
	while(num != 0)
	{
		if (num > 0)
		{
			sum += num;
		}
		cin >> num;
	}

	cout << "The sum of the positive integers is " << sum << endl;
}

// eof isumit.c $Id: isumit.cpp 1111 2007-11-28 22:14:52Z boudreat $
