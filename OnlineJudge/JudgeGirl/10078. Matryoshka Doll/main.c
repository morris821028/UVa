#include "doll.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	Doll *dolls[16];
	dolls[0] = newDoll('<', '~');
	dolls[1] = newDoll('(', ')');
	dolls[2] = newDoll('@', '>');
	dolls[3] = newDoll('#', '#');
	package(dolls[1], dolls[2]);
	package(dolls[0], dolls[1]);
	printf("%s\n", doll_c_str(dolls[0]));
	printf("%s\n", doll_c_str(dolls[3]));
	package(dolls[3], dolls[1]);
	printf("%s\n", doll_c_str(dolls[3]));
	printf("%s\n", doll_c_str(dolls[0]));
	return 0;
}
