#include <bits/stdc++.h>
using namespace std;

unsigned int seed = 0;
unsigned int p_random() {return seed = (seed*9301+49297);}

unsigned int A[5000005];
int main() {
	int N, M, S, x, y;
	unsigned int hash = 0;
	scanf("%d %d %d", &N, &M, &S);
	seed = S;
	for (int i = 1; i <= N; i++)
		A[i] = p_random();
	for (int i = 0; i < M; i++) {
		x = p_random()%N+1, y = p_random()%N+1;
		if (x > y)	swap(x, y);
		unsigned int max_val = A[x];
		for (int j = x; j <= y; j++)
			max_val = max(max_val, A[j]);
		hash ^= max_val; 
	}
	printf("%lu\n", hash);
	return 0;
}
