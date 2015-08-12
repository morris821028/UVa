#include <bits/stdc++.h> 
using namespace std;

int main() {
	int n, m, A[1024], x, y;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		printf("%d\n", A[x] + A[y]);
	}
	return 0;
}
