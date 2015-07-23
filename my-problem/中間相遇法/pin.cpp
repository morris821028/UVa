#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

typedef unsigned short int UINT16;
class SimpleIdea {
public:
	UINT16 key;
	SimpleIdea(UINT16 k = 0):
		key(k) {}
	UINT16 encrypt(UINT16 m) {
		return (rotate_left(m, key&15) + key)^key;
	}
	UINT16 decrypt(UINT16 m) {
		return rotate_left((m^key)+(~key)+1, 16 - (key&15));
	}
private:
	UINT16 rotate_left(UINT16 x, UINT16 n) {
    	return  (x << n) | (x >> (16-n));
	}
} test, T1, T2;

int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 5; 
	while (testcase--) {
		T1.key = rand()%(1<<16);
		T2.key = rand()%(1<<16);
		int a = rand()%(1<<16);
		printf("%d %d\n", T2.encrypt(T1.encrypt(a)), a);
	}	
	return 0;
}
