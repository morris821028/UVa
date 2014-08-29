#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
#define maxL (1000000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
long long P[100000];
int Pt = 0;
void sieve() {
    register int i, j, k, l;
    SET(1);
    int n = 1000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(j = i + i; j <= n; j += i)
                SET(j);
            P[Pt++] = i;
        }
    }
}

vector< pair<long long, int> > factor(long long n) {
	vector< pair<long long, int> > R;
	
	for(int i = 0, j; i < Pt && P[i] * P[i] <= n; i++) {
		if(n%P[i] == 0) {
			for(j = 0; n%P[i] == 0; n /= P[i], j++);
			R.push_back(make_pair(P[i], j));
		}
	}
	if(n != 1)	R.push_back(make_pair(n, 1));
	return R;
}

void make(int idx, long long m, vector< pair<long long, int> > &v, vector<long long> &f, int limit) {
    if (m > limit)
        return;
	if(idx == v.size()) {
        f.push_back(m);
		return;
	}
	long long a = m, b = v[idx].first;
	for(int i = v[idx].second; i >= 0; i--)
		make(idx + 1, a, v, f, limit), a *= b;
}

long long gcd(long long a, long long b) {
    for (long long t; a%b; t = a, a = b, b = t%b);
    return b;
}
long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}
int main() {
    sieve();
    long long n;
    int cases = 0;
    while (scanf("%lld", &n) == 1 && n) {
        vector< pair<long long, int> > f = factor(n);
        vector<long long> div;
        make(0, 1, f, div, 1000000);
        printf("Scenario %d:\n", ++cases);
        sort(div.begin(), div.end());
        
        int cnt = 0;
        for (int i = 0; i < div.size(); i++) {
            for (int j = i + 1; j < div.size(); j++) {
                long long d = lcm(div[i], div[j]);
                if (div[j] - div[i] > 25)
                    break;
                for (int k = j + 1; k < div.size(); k++) {
                    if (div[k] - div[i] > 25)
                        break;
                    long long dd = lcm(d, div[k]);
                    if (dd == n) {
                        printf("%lld %lld %lld\n", div[i], div[j], div[k]);
                        cnt++;
                    }
                }
            }
        }
        if (cnt == 0) {
            puts("Such bells don't exist");
        }
        puts("");
    }
    return 0;
}

/*
 10
 
 103
 
 0
 */