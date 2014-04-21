#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	for(int n; scanf("%d", &n) == 1; ) {
		vector< pair<int, int> > D;
		for(int i = 0, x, y; i < n; i++) {
			scanf("%d %d", &x, &y);
			D.push_back(make_pair(x, y));
		}
		sort(D.begin(), D.end());
		for(int i = 0; i < D.size(); i++)
			printf("%d %d\n", D[i].first, D[i].second);
	}
	return 0;
}
