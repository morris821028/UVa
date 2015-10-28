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
    	n = rand()%50+1;
    	n = 1;
    	printf("%d\n", n);
    	for (int i = 0; i < n; i++) {
    		m = rand()%50+1;
    		printf("%d\n", m);
    		for (int j = 0; j < m; j++) {
    			int o = rand()%50+1;
    			printf(" %d", o);
    			for (int k = 0; k < o; k++) {
    				int x = rand()%1000+1;
    				if (rand()%10 == 0)	x = -x;
    				printf(" %d", x);
    			}
    			puts("");
			}
		}
	}
    return 0;
}
