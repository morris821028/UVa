#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int bsearch(int x, int n) {
	int l = 0, r = n-1, mid;
	int L = 0;
	while (l <= r) {
		mid = (l + r)/2, L++;
		if (mid == x)
			return L;
		if (x < mid)
			r = mid - 1;
		else
			l = mid + 1;
	}
	return L;
}
const int MAXN = 10000;
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		vector<int> A;
		vector< pair<int, int> > B;
		for (int i = n+1; i <= MAXN; i++) {
			if (bsearch(n, i) == m)
				A.push_back(i);
		}
		
		for (int i = 0; i < A.size(); ) {
			int l = A[i], r = A[i];
			while (i < A.size() && r == A[i])
				r++, i++;
			B.push_back(make_pair(l, r - 1));
		}
		
		printf("%d\n", B.size());
		for (int i = 0; i < B.size(); i++)
			printf("%d %d\n", B[i].first, B[i].second);
	}
	return 0;
}
