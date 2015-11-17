#include <stdio.h>
#include "set.h"
int main() {
	Set a, b, c;
	
	init(&a);
	add(&a, 3);
	add(&a, 5);
	add(&a, 2);
	
	init(&b);
	add(&b, 3);
	add(&b, 7);
	add(&b, 9);
	
	c = setUnion(a, b);
	has(c, 2);
	has(c, 3);
	has(c, 5);
	has(c, 7);
	has(c, 9);
	
	c = setIntersect(a, b);
	has(c, 2);
	has(c, 3);
	has(c, 5);
	has(c, 7);
	has(c, 9);
	
	c = setDifference(a, b);
	has(c, 2);
	has(c, 3);
	has(c, 5);
	has(c, 7);
	has(c, 9);
	return 0;
}
