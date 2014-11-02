#include <stdio.h> 
#include <algorithm>
#include <vector>
#include <stdlib.h>
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		int A[32][32] = {}, x, city_id, dest, k;
		int north[32], south[32];
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &city_id, &k);
			for (int j = 0; j < k; j++) {
				scanf("%d %d", &dest, &x);
				A[city_id][dest] += x;
			}
		}
		vector< pair<int, int> > ret;
		for (; scanf("%d", &city_id) == 1 && city_id;) {
			for (int i = 0; i < n; i++)
				scanf("%d", &north[i]);
			for (int i = 0; i < n; i++)
				scanf("%d", &south[i]);
			int load = 0;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					load += A[north[i]][south[j]] * (abs(i - j) + 1);
			ret.push_back(make_pair(load, city_id));
		}
		sort(ret.begin(), ret.end());
		puts("Configuration Load");
		for (int i = 0; i < ret.size(); i++) {
			printf("%5d         %d\n", ret[i].second, ret[i].first);
		}
	}
	return 0;
}
