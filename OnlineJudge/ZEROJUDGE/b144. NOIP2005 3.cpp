#include <bits/stdc++.h>
using namespace std;

const int MAXN = 65536;
int A[MAXN][2], C[MAXN<<1], CNT[MAXN];
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 1; i <= n; i++)
			scanf("%d %d", &A[i][0], &A[i][1]);
		int ret = 0, err = 0;
		C[1] = 1;
		for (int u = 1, next = A[1][0], i = 2; next != 1;) {
			if (A[next][0] == u) {
				u = next;
				C[i++] = u;
				next = A[next][1];
			} else if (A[next][1] == u) {
				u = next;
				C[i++] = u;
				next = A[next][0];
			} else {
				err = 1;
				break;
			}
		}
		
		if (err) {
			puts("-1");
			break;
		}
					
		memset(CNT, 0, sizeof(CNT));
		for (int i = 1; i <= n; i++) {
			if (i - C[i] >= 0)	CNT[i - C[i]]++;
			else				CNT[i - C[i] + n]++;
		}
		for (int i = 0; i < n; i++)
			ret = max(ret, CNT[i]);
			
		reverse(C+2, C+2+(n-1));
		memset(CNT, 0, sizeof(CNT));
		for (int i = 1; i <= n; i++) {
			if (i - C[i] >= 0)	CNT[i - C[i]]++;
			else				CNT[i - C[i] + n]++;
		}
		for (int i = 0; i < n; i++)
			ret = max(ret, CNT[i]);
			
		printf("%d\n", n - ret);
		break;
	}
	return 0;
}
