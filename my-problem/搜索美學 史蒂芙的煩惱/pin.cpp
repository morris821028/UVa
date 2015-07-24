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

int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 1; 
	while (testcase--) {
		int n = 50000;
		printf("%d\n", n);
//		set< pair<int, int> > S;
//		for (int i = 0; i < n; i++) {
//			do {
//				x = rand(), y = rand();
//				if (!S.count(make_pair(x, y)))
//					break;
//			} while (true);
//			printf("%d %d\n", x, y);
//			S.insert(make_pair(x, y));
//			do {
//				x = rand(), y = rand();
//				if (!S.count(make_pair(x, y)))
//					break;
//			} while (true);
//			printf("%d %d\n", x, y);
//			S.insert(make_pair(x, y));
//		}
		set< pair<int, int> > S;
		for (int i = 0; i < n; i++) {
			do {
				if (rand()%2)
					x = rand()%300, y = rand()%300;
				else
					x = rand()%500 + 30000, y = rand()%500 + 30000;
				if (!S.count(make_pair(x, y)))
					break;
			} while (true);
			printf("%d %d\n", x, y);
			S.insert(make_pair(x, y));
			do {
				if (rand()%2)
					x = rand()%500, y = rand()%500;
				else
					x = rand()%300 + 30000, y = rand()%300 + 30000;
				if (!S.count(make_pair(x, y)))
					break;
			} while (true);
			printf("%d %d\n", x, y);
			S.insert(make_pair(x, y));
		}
//		vector< pair<int, int> > A;
//		for (int i = 0; i < 300; i++)
//			for (int j = 0; j < 300; j++)
//				A.push_back(make_pair(i, j));
//		random_shuffle(A.begin(), A.end());
//		assert(A.size() >= 2 * n);
//		for (int i = 0; i < n; i++) {
//			printf("%d %d\n", A[2*i].first, A[2*i].second);
//			printf("%d %d\n", A[2*i+1].first, A[2*i+1].second);
//		}
	}	
	return 0;
}
