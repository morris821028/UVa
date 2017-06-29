#include <bits/stdc++.h>
#include <random>
using namespace std;
double frandom() {
	return (double)(rand()%10) / 2;
}
double mrandom() {
	return (rand() * rand())%10;
}
int main() {
//	freopen("test.in", "w", stdout);
    srand(time(NULL));
    int testcase = 5000;
    while (testcase--) {
    	int n, m1, m2;
    	n = (1U<<30) - rand()%1000000 - 1;
    	m1 = rand()%1000000;
		m2 = rand()%1000000;
    	printf("%d %d %d\n", n, m1, m2);
	}
    return 0;
}
