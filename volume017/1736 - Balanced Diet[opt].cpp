#include <bits/stdc++.h>
using namespace std;
const int MAXM = 100005;
/* 
 before: n f_i - 1 < s_i 
 after : s_i + 1 < f_i (n+1) + 1
 
 f_i = a_i / tot_a
 s_i + 1 < f_i (n+1) + 1
 	=> (s_i * tot_a)/a_i < n
*/ 
struct Node {
	int n, i;
	Node() {}
	Node(int n, int i): n(n), i(i) {}
	bool operator<(const Node &x) {
		return n > x.n;
	}
};
int main() {
	int M, K;
	while (scanf("%d %d", &M, &K) == 2) {
		static int a[MAXM], s[MAXM];
		int64_t tot = 0;
		memset(s, 0, sizeof(s[0])*M);
		for (int i = 0; i < M; i++)
			scanf("%d", &a[i]), tot += a[i];
		for (int i = 0; i < K; i++) {
			int b;
			scanf("%d", &b);
			s[b-1]++;
		}
		
		static Node S[MAXM];
		for (int i = 0; i < M; i++)
			S[i] = {((s[i]+1)*tot + a[i]-1)/a[i], i};
		make_heap(S, S+M);
		
		int n;
		for (n = K+1; ;) {
			auto it = S[0];
			if (it.n < n) {
				n = it.n;
				break;
			}
			pop_heap(S, S+M);
			int i = it.i;
			s[i]++;
			S[M-1] = {((s[i]+1)*tot + a[i]-1)/a[i], i};
			push_heap(S, S+M);
			n++;
			if (n%tot == 0)
				break;
		}
		if (n%tot == 0)
			puts("forever");
		else
			printf("%d\n", n-K-1);
	}
	return 0;
}
/*
6  5
2  1  6  3  5  3
1  2  5  3  5

6  4
2  1  6  3  5  3
1  2  5  3
*/
