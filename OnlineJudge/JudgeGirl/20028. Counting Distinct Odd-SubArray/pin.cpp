#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	int testcase = 100;
    while (testcase--) {
    	int n = 100;
    	int k = n/5;
    	printf("%d %d\n", n, k);
    	for (int i = 0; i < n; i++) {
    		int v = rand()%10;
    		if (rand()%2000 == 0)
    			v = 1;
    		printf("%d%c", v, " \n"[i==n-1]);
		}
    }
	return 0;
}

