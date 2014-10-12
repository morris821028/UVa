#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
#define maxL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[32767], Pt;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 50000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
vector< pair<int, int> > factor(int n) {
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
int main() {
	sieve();
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		vector< pair<int, int> > f = factor(n);
		int sign = 0;
		for (int i = 0; i < f.size(); i++) {
			if (f[i].first == 2) {
			} else {
				if ((f[i].first - 1)%4 == 0)
					sign += f[i].second;
			}
		}
		puts(sign&1 ? "-" : "+");
	}
	return 0;
}
