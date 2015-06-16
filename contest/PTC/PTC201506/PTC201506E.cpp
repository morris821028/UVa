#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 205; 
const int MAXLOGK = 11; 
int powA[2][MAXN][MAXN], retA[MAXN][MAXN], retB[MAXN][MAXN];
inline void product(int N, int A[][MAXN], int B[][MAXN], int C[][MAXN]) {
	for (int i = 0; i < N; i++)
		memset(C[i], 0, sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
        	if (A[i][k])
            for(int j = 0; j < N; j++) {
            	if (B[k][j])
            	C[i][j] = max(C[i][j], A[i][k] + B[k][j]);
            }
        }
    }
}
void compute(int N, int K) {
	for (int i = 0; i < N; i++)
		memset(retA, 0, sizeof(int)*4);
	int p = 0, q = 1;
	int f = 1;
	while (K) {
		if (K&1) {
			if (f) {
				f = 0;
				for (int i = 0; i < N; i++)
					memcpy(retA[i], powA[p][i], sizeof(int) * N);
			} else {
				product(N, retA, powA[p], retB);
				for (int i = 0; i < N; i++)
					memcpy(retA[i], retB[i], sizeof(int) * N);
			}
		}
		K >>= 1;
		product(N, powA[p], powA[p], powA[q]);
		p = 1 - p, q = 1 - q;
	}
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
    	int N, M, K, Q;
    	scanf("%d %d %d %d", &N, &M, &K, &Q);
    	for (int i = 0; i < N; i++)
    		for (int j = 0; j < N; j++)
    			powA[0][i][j] = 0;
    	for (int i = 0; i < M; i++) {
    		int u, v, w;
    		scanf("%d %d %d", &u, &v, &w);
    		u--, v--;
    		powA[0][u][v] = max(powA[0][u][v], w);
    	}
    	compute(N, K);
    	for (int i = 0; i < Q; i++) {
    		int u, v;
    		scanf("%d %d", &u, &v);
    		u--, v--;
    		printf("%d\n", retA[u][v]);
    	}
    }
    return 0;
}
/*
3
3 3 2 3
1 2 3
2 3 4
3 1 2
1 2
2 1
1 3

3 4 10 2
1 2 1000
2 3 100
3 1 10
1 3 1
2 2
3 2

3 4 1000 2
1 2 1000
2 3 100
3 1 10
1 3 1
2 2
3 2
*/
