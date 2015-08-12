#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
int A[MAXN], used[MAXN], f = 0;
int N, M;
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		memset(used, 0, sizeof(int) * (M+1));
		
		int st = N-1;
		for (int i = 0; i < N-1; i++) {
			if (used[A[i]]) {
				st = i; 
				break;
			}
			used[A[i]] = 1;
		}
		
		set<int> S;
		for (int i = 1; i <= M; i++) {
			if (used[i] == 0)
				S.insert(i);
		}
		
		int f = 1;
		while (true) {
			set<int>::iterator it = S.upper_bound(A[st]);
			if (f == 0) {
				used[A[st]] = 0;
				S.insert(A[st]);
			}
			if (it != S.end()) {
				A[st++] = *it;
				used[*it] = 1;
				break;
			} else {
				if (f == 1)	f = 0;
				st--;
			}
		}
		
		for (int i = 1; i <= M && st < N; i++) {
			if (used[i] == 0)
				A[st++] = i;
		}
		
		for (int i = 0; i < N; i++)
			printf("%d%c", A[i], i == N-1 ? '\n' : ' ');
	}
	return 0;
}
/*
3
1 2
1
2 2
1 1
2 2
1 2
*/
