#include <bits/stdc++.h>
#include <random>
using namespace std;
double frandom() {
	return (double)(rand()%10) / 2;
}
double mrandom() {
	return (rand() * rand())%10;
}
unsigned int urand() {
	return rand();
}
int main() {
	freopen("in.txt", "w", stdout);
    srand(time(NULL));
    int testcase = 5000;
    while (testcase--) {
    	int l, r;
    	r = urand()*urand()*urand()%INT_MAX+1;
    	int gap = urand()*urand()*urand()%100000;
    	l = max(r - gap, 1);
    	if (l > r) swap(l, r);
    	printf("%d %d\n", l, r);
	}
    return 0;
}
