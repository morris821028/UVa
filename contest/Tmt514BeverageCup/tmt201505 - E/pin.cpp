#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <set>
#include <algorithm>
using namespace std;
double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}

int vvv[20] = {885828, 737167, 898961, 748096,
854425, 732894, 706721, 606199,
-971645, 988877, -838743, 853618,
993753, -652232, 991850, -650983,
620105, 659001, 916399, 973880};
main() {
	int n, m, t, a, b, c, tmp;
	int z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	
	int T = 10000;
	printf("%d\n", T);
	while(T--) {
		int n = 30, m = rand()%n + 1;
		printf("%d\n", n);
		set< pair<int, int> > S;
		S.insert(make_pair(0, 0));
		printf("%d %d\n", 0, 0);
		for (int i = 1; i < n; i++) {
			int x, y;
			do {
				if (rand()%10 < 8) {
					x = vvv[rand()%20], y = vvv[rand()%20];
					if (rand()%2)	x = -x;
					if (rand()%2)	y = -y;
				} else {
					x = rand()%100 - 50, y = rand()%100 - 50;
				}
			} while (S.count(make_pair(x, y)));
			S.insert(make_pair(x, y));
			printf("%d %d\n", x, y);
		}		
	}
	
	return 0;
}
