#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;
double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}
int x[100005] = {}, y[100005] = {}, used[100005] = {};
main() {
	int n, m, t, a, b, c, tmp;
	int z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 1;
	T = 10;
	while(T--) {
		n = 10000;
		printf("%d\n", n);
		for (int i = 0; i < n; i++) {
			if (i == 0)
				puts("0");
			else {
				m = rand()%3 + 1;
				vector<int> ll;
				for (int j = 0; j < m; j++) 
					ll.push_back(rand()%i + 1);
				sort(ll.begin(), ll.end());
				std::vector<int>::iterator it;
  				it = std::unique (ll.begin(), ll.end());   // 10 20 30 20 10 ?  ?  ?  ?
                                                         //                ^
  				ll.resize( std::distance(ll.begin(),it) ); // 10 20 30 20 10
  				for (int i = 0; i < ll.size(); i++)
  					printf("%d ", ll[i]);
				puts("0");
			}
		}
		puts("");
	}
	T = 5; 
	while(T--) {
		n = 30000;
		printf("%d\n", n);
		for (int i = 0; i < n; i++) {
			if (i == 0)
				puts("0");
			else {
				m = rand()%3;
				vector<int> ll;
				for (int j = 0; j < m; j++) 
					ll.push_back(max(0, i - rand()%10 - 1) + 1);
				sort(ll.begin(), ll.end());
				std::vector<int>::iterator it;
  				it = std::unique (ll.begin(), ll.end());   // 10 20 30 20 10 ?  ?  ?  ?
                                                         //                ^
  				ll.resize( std::distance(ll.begin(),it) ); // 10 20 30 20 10
  				for (int i = 0; i < ll.size(); i++)
  					printf("%d ", ll[i]);
				puts("0");
			}
		}
		puts("");
	}
	return 0;
}
