#include <stdio.h> 
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
#define MAX_N 100005 
struct zkwST {
	int M;
	pair<long long, int> st[262144 + 10];
	pair<long long, int> elem[131072 + 10];
	zkwST() {
	}
	void build(int n) {
		for(M = 1; M < n+1; M <<= 1);
		for(int i = 2*M-1; i > 0; i--) {
            if(i >= M) {
            	if(i - M > n)	
					st[i] = make_pair(0, 0);
            	else
                	st[i] = elem[i - M];
            } else {
            	st[i].first  = st[i<<1].first  + st[i<<1|1].first;
            	st[i].second = st[i<<1].second + st[i<<1|1].second;
            }
        }
	}
	pair<long long, int> prefixQuery(long long S) {
		pair<long long, int> ret = make_pair(0LL, 0);
		int s;
		for(s = 1; s < M; ) {
			if(st[s<<1].first <= S) {
				ret.first  += st[s<<1].first;
				ret.second += st[s<<1].second;
				S -= st[s<<1].first;
				s = s<<1|1;
			} else {
				s = s<<1; 
			}
		}
		if(st[s].first <= S) {
			ret.first  += st[s].first;
			ret.second += st[s].second;
		}
		return ret;
	}
	void singleUpdate(int index, pair<long long, int> val) {
		st[index + M] = elem[index] = val;
		for(int s = (index + M)>>1; s > 0; s >>= 1) {
        	st[s].first  = st[s<<1].first  + st[s<<1|1].first;
        	st[s].second = st[s<<1].second + st[s<<1|1].second;
		}
	}
};

int C[MAX_N], D[MAX_N];
int A[MAX_N], B[MAX_N], mapB[MAX_N];
int N, K;
long long M;
zkwST segTree;
bool cmpD(int i, int j) {
	return D[i] < D[j];
}
bool cmpC(int i, int j) {
	return C[i] < C[j];
}
struct cmpPQ {
	bool operator()(pair<int, int> &a, pair<int, int> &b) const {
		return a.first > b.first;
	}
};
int main() {
	int testcase;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &K);
		scanf("%lld", &M);
		for(int i = 0; i < N; i++) {
			scanf("%d %d", &C[i], &D[i]);
			A[i] = B[i] = i;
		} // Di <= Ci
		
		sort(A, A + N, cmpD);
		sort(B, B + N, cmpC);
		
		// build no-sale price with prefix-interval-query struct.
		for(int i = 1; i <= N; i++) {
			mapB[B[i-1]] = i;
			segTree.elem[i] = make_pair((long long)C[B[i-1]], 1);
		}
		segTree.build(N);
		
		// sweeping by sale price (small to large)
		priority_queue< pair<int, int>, vector< pair<int, int> > , cmpPQ > pQ; 
			// pQ maintain size() <= K
		int ret = segTree.prefixQuery(M).second;
		long long pQcost = 0;
		for(int i = 0; i < N; i++) {
			pQcost += D[A[i]]; // add sale price
			pQ.push(make_pair(C[A[i]] - D[A[i]], A[i])); // <different price, index>
			if(pQ.size() > K) {
				pair<int, int> p = pQ.top();
				pQ.pop();
				pQcost += p.first;
			}
			segTree.singleUpdate(mapB[A[i]], make_pair(0, 0));
			if(pQcost > M)
				break;
			ret = max(ret, segTree.prefixQuery(M - pQcost).second + i+1);
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
100

10 9 819
54 49
95 43
89 40
89 84
64 60
69 58
99 88
78 34
83 62
93 77


10 1 267
52 25
51 17
88 58
86 82
61 55
38 33
36 2
97 44
100 100
85 1

4 2 15
20 3
40 4
50 7
8 8 

4 1 11
20 3
40 4
50 7
8 8 

4 2 15
20 3
40 4
50 7
8 8 
*/
