#include <stdio.h> 
#include <map>
// greedy 
#include <algorithm> 
using namespace std;

int main() {
	int n, m, x;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		map<int, int> R, C, T;
		for (int i = 0; i < n; i++)
			scanf("%d", &x), R[x]++, T[x] = 0;
		for (int i = 0; i < m; i++)
			scanf("%d", &x), C[x]++, T[x] = 0;
		int ret = 0;
		for (map<int, int>::iterator it = T.begin();
			it != T.end(); it++) {
			x = it->first;
			ret += max(R[x], C[x]) * x;
		}
		printf("%d\n", ret);
	}
	return 0;
}
