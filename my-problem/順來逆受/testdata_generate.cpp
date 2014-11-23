#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <queue>
#include <set>
#include <map> 
#include <functional>
#include <math.h>
#include <string.h>
using namespace std;

double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}
int A[262144] = {};
main() {
	int n, m, t, a, b, c, tmp;
	int x, y, z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 100;
	while(T--) {
		n = 5, m = 6;
		printf("%d %d\n", n, m);
		set< pair<int, int> > S;
		int remove[65536] = {};
		for (int i = 0; i < m; i++) {
			do {
				x = rand()%n, y = rand()%n;
				if (x > y) swap(x, y);
				if (x != y && S.find(make_pair(x, y)) == S.end())
					break;
			} while (true);
			printf("%d %d\n", x + 1, y + 1);
			S.insert(make_pair(x, y));
		}
		q = 10;
		printf("%d\n", q);
		for (int i = 0; i < q; i++) {
			int ok = 0;
			if (rand()%100 < 20) {
				for (int j = 0; j < 10; j++) {
					x = rand()%m;
					if (remove[x] == 0) {
						remove[x] = 1;
						printf("D %d\n", x+1);
						ok = 1;
						break;
					}
				}
			}
			if (!ok) {
				printf("Q %d\n", rand()%n + 1);
			}
		}
		puts("");
	}
	return 0;
}
