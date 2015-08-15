#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
using namespace std;

double random() {
	return (double) rand() / RAND_MAX;
}
const int MAXN = 131072;
int parent[MAXN], weight[MAXN];
void init(int n) {
    for(int i= 0; i <= n; i++)
        parent[i] = i, weight[i] = 1;
}
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y) return 0;
    if(weight[x] > weight[y])
        weight[x] += weight[y], parent[y] = x;
    else
        weight[y] += weight[x], parent[x] = y;
    return 1;
}

int fa[131072];
int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 1; 
	while (testcase--) {
		n = 100000, m = 100000;
		init(n);
		printf("%d %d\n", n, m);
//		for (int i = 2; i <= n; i++) {
//			if (i <= n)
//				printf("news %d %d\n", i, fa[i] = rand()%(i-1)+1);
//			else
//				printf("news %d %d\n", i, fa[i] = i - 1);
//		}
//		for (int i = n-1; i < m; i++) {
		for (int i = 0; i < m; i++) {
			if (rand()%2) {
				x = rand()%n+1;
				y = rand()%n+1;
				printf("sim %d %d\n", x, y);
			} else {
				int test = 0;
				do {
					x = rand()%n+1, test++;
					if (x == 1)			continue;
					if (x - fa[x] < 20 && test < 10000)	continue;
					if (x < 200)
						y = rand()%(x-1)+1;
					else
						y = x - rand()%10 - 1;
					break;
				} while (true);
				assert(y < x);
				fa[x] = y;
				printf("news %d %d\n", x, y);
			}
		}
	}	
	return 0;
}
