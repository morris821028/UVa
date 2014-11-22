#include <stdio.h>
#include <map> 
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 1024
const long long MAXVAL = 1e+16, MAXVAL2 = 1e+15;
long long C[MAXN][MAXN] = {};
map<long long, vector< pair<long long, long long> > > R;
int testCombination(long long n, long long m, long long Cnm) { // test C(n, m), m < 10
	long long ret = 1;
	m = min(m, n-m);
	for (long long i = 1; i <= m; i++) {
		if (Cnm * i / (n + 1 - i) / ret  < 1)
			return 1;
		ret = ret * (n + 1 - i) / i;
	}
	return ret == Cnm ? 0 : -1;
}
vector< pair<long long, long long> > invCombination(long long n) {
	vector< pair<long long, long long> > ret;
	ret = R[n];
	for (int i = 1; i < 10; i++) {
		long long l = 1, r = n, mid;
		while (l <= r) {
			mid = (l + r)/2;
			int f = testCombination(mid, i, n); // {-1, 0, 1}
			if (f == 0) {
				ret.push_back(make_pair(mid, i));
				ret.push_back(make_pair(mid, mid - i));
				break;
			}
			if (f < 0)
				l = mid + 1;
			else
				r = mid - 1;
		}
	}
	sort(ret.begin(), ret.end());
	ret.resize(unique(ret.begin(), ret.end()) - ret.begin());
	return ret;
}
int main() {
//	printf("%d\n", testCombination(5000, 2, 12497500));
	C[0][0] = 1;
	for (int i = 1; i < MAXN; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = C[i-1][j-1] + C[i-1][j];
			C[i][j] = min(C[i][j], MAXVAL);
			if (j != i && C[i][j] <= MAXVAL2)
				R[C[i][j]].push_back(make_pair(i, j));
		}
	}
//	for (int i = 0; i < 10; i++)
//		printf("%lld\n", C[MAXN-1][i]);
	int testcase;
	long long n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld", &n);
		vector< pair<long long, long long> > r = invCombination(n);
		printf("%d\n", (int) r.size());
		for (int i = 0; i < r.size(); i++)
			printf("(%lld,%lld)%c", r[i].first, r[i].second, i == r.size()-1 ? '\n' : ' ');
	}
	return 0;
}
