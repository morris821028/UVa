#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
#define maxL (30000000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
int P[5500], Pt = 0;
int F[30000005] = {};
void sieve() {
    register int i, j, k, l;
    SET(1);
    int n = 50000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(j = i + i; j <= n; j += i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
vector< pair<int, int> > factor(int n) {
	int on = n;
	vector< pair<int, int> > R;
	
	for(int i = 0, j; i < Pt && P[i] * P[i] <= n; i++) {
		if(n%P[i] == 0) {		
			for(j = 0; n%P[i] == 0; n /= P[i], j++);
			R.push_back(make_pair(P[i], j));
		}
	}
	if(n != 1)	R.push_back(make_pair(n, 1));
	return R;
}
void make(int idx, int n, int m, vector< pair<int, int> > &v) {
	if(idx == v.size()) {
		if((n&m) == m)
			F[n]++;
		return;
	}
	int a = m, b = v[idx].first;
	for(int i = v[idx].second; i >= 0; i--)
		make(idx + 1, n, a, v), a *= b;
}
int main() {
	sieve();
	vector< pair<int, int> > ff;
	for(int i = 1; i <= 30000000; i++) {
		ff = factor(i);
		make(0, i, 1, ff);
	}
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		int ret = 0;
		for(int i = 1; i <= n; i++)
			ret += F[i];
		printf("%d\n", ret - n);
	}
	return 0;
}
