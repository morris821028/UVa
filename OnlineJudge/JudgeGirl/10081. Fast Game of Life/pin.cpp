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
	freopen("in.txt", "w", stdout);
    srand(time(NULL));
    int testcase = 1;
//    printf("%d\n", testcase);
    while (testcase--) {
    	int n, m;
    	n = 2000;
    	m = 100;
    	printf("%d %d\n", n, m);
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < n; j++) {
    			printf("%d", rand()%2);
			}
			puts("");
		}
	}
    return 0;
}
