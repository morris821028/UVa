#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int rank[100005], parent[100005];
void init(int N) {
	for(int i = 0; i <= N; i++) {
		rank[i] = 1, parent[i] = i;
	}
}
int findp(int x) {
	return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if(x == y) 
		return 0;
	if(rank[x] > rank[y])
		rank[x] += rank[y], parent[y] = x;
	else
		rank[y] += rank[x], parent[x] = y;
	return 1;
}
int main()  {
	int testcase;
	int error_group[100005];
	int error_test[100005], error_label[100005] = {}, ecases = 1;
	scanf("%d", &testcase);
	while(testcase--) {
		int N, M, K;
		int A, I, B, J, C;
		int i, j, k;
		int NIL; // error group
		int global_solv = 1;
		scanf("%d %d %d", &N, &M, &K);
		NIL = N * K;
		init(N*K);// [0, N-1][0, K-1]
		for(i = N*K; i >= 0; i--)
			error_group[i] = 0;
		for(i = 0; i < M; i++) {
			scanf("%d %d %d %d %d", &A, &I, &B, &J, &C);
			I--, J--;
			int Vi, Vj;
			if(!global_solv)
				continue;
			int ok = 0;
			if(A == 0 && B == 0) {
				ok = (C == 0);
			} else if(A == 0) {
				for(j = 1; j <= K; j++) {
					if(B * j != C)
						joint(NIL, J*K + (j-1));
					else
						ok = 1;
				}
			} else if(B == 0) {
				for(j = 1; j <= K; j++) {
					if(A * j != C)
						joint(NIL, I*K + (j-1));
					else
						ok = 1;
				}
			} else {
				if(C%__gcd(A, B) == 0) {
					for(j = 1; j <= K; j++) {
						Vi = j, Vj = (C - A * Vi)/B;
						if(Vj < 1 || Vj > K || A * Vi + B * Vj != C)
							joint(NIL, I*K + Vi-1);
						else
							joint(I*K + Vi-1, J*K + Vj-1), ok = 1;
						Vj = j, Vi = (C - B * Vj)/A;
						if(Vi < 1 || Vi > K || A * Vi + B * Vj != C)
							joint(NIL, J*K + Vj-1);
						else
							joint(I*K + Vi-1, J*K + Vj-1), ok = 1;
					}
				}		
			}
			global_solv &= ok;
		}
		error_group[findp(NIL)] = 1;
		for(i = 0; i < N && global_solv; i++) {
			ecases++;
			for(j = 0; j < K; j++) {
				int p = findp(i*K + j);
				if(error_label[i*K + j] != ecases)
					error_label[i*K + j] = ecases, error_test[p] = 0;
				error_test[p]++;
				if(error_test[p] > 1)
					error_group[p] = 1;
			}
		}
		for(i = 0; i < N && global_solv; i++) {
			int ok = 0;
			//printf("x%d = ", i+1);
			for(j = 0; j < K; j++) {
				int p = findp(i*K + j); 
				if(error_group[p] == 0) {
					ok = 1;
					//printf("%d", j+1);
					break;
				}
			}
			//puts("");
			global_solv &= ok;
		}
		puts(global_solv ? "yes" : "no");
	}
	return 0;
}
