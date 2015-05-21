#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
// O(n), BWT compress inverse
const int MAXN = 2048;
char s[MAXN];
int K[MAXN], M[MAXN], C[MAXN], N;
int main() {
	int testcase, e_pos;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s %d", s, &e_pos), e_pos--;
		
		string L(s), F(s);
		N = L.length();
		
		memset(K, 0, sizeof(K));
		memset(M, 0, sizeof(M));
		memset(C, 0, sizeof(C));
		
		for (int i = 0; i < N; i++) {
			C[i] = K[L[i]];
			K[L[i]]++;
		}
		
		sort(F.begin(), F.end());
		for (int i = 0; i < N; i++) {
			if (i == 0 || F[i] != F[i-1])
				M[F[i]] = i;
		}
		
		string T(N, '?');
		for (int i = 0; i < N; i++) {
			T[N-1-i] = L[e_pos];
			e_pos = C[e_pos] + M[L[e_pos]];
		}
		puts(T.c_str());
	}
	return 0;
}
/*
2
CGA
3
NNBAAA
4 
*/
