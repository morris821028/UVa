#include <bits/stdc++.h>
const int MAXN = 1048676;
int BIT[MAXN];
int query(int idx, int N, int dir) {
	int sum = 0;
	for (; idx > 0 && idx <= N; idx += dir*(idx&(-idx)))
		sum += BIT[idx];
	return sum;
}
void modify(int idx, int N, int dir, int val) {
	for (; idx > 0 && idx <= N; idx += dir*(idx&(-idx)))
		BIT[idx] += val;
}
char s[MAXN];
int A[MAXN];
int main() {
	while (scanf("%s", s) == 1) {
		int n = strlen(s);
		int y = 0, e = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == 'y')
				A[i] = y*3, y++;
			else
				A[i] = (e/2)*3 + e%2 + 1, e++;
		}

		for (int i = 1; i <= n; i++)
			BIT[i] = 0;
		int ret = 0;
		for (int i = 0; i < n; i++) {
			A[i]++;
			ret += query(A[i]+1, n, 1);
			modify(A[i], n, -1, 1);
		}
		printf("%d\n", ret);
	}
	return 0;
}