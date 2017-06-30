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
//	freopen("in.txt", "w", stdout);
    srand(time(NULL));
    int N;
    int testcase = 1;
    printf("%d\n", testcase);
    while (testcase--) {
    	for (int it = 0; it < 3; it++) {
    		int n = 10000;
    		printf("%d\n", n);
	    	for (int i = 0; i < n; i++) {
	    		while (1) {
		    		int lx = rand()%(1920*4);
		    		int ly = rand()%(1080*4);
		    		int rx = lx + rand()%128+64;
		    		int ry = ly + rand()%128+64;
		    		if (lx < rx && ly < ry) {
		    			printf("%d %d %d %d\n", lx, ly, rx, ry);
		    			break;
					}
	    		}
			}
		}
    	puts("");
	}
    return 0;
}
/*
GCGCAATG
3 1 1 3 0 0 2 1
GCCCTAGCG
2 0 3 2 0 1 2 0 1
*/
