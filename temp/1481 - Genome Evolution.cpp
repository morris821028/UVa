#include <stdio.h> 
#include <algorithm>
using namespace std;
// find A and A', #(set(A[l, r]) = set(A'[p, q]))
#define MAXN 4096
int A[MAXN], B[MAXN], R[MAXN];
int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < n; i++)
			scanf("%d", &B[i]), R[B[i]] = i;
		
		int ret = 0, l, r;
		for (int i = 0; i < n; i++) {
			l = r = R[A[i]];
			for (int j = i+1, sz = 1; j < n; j++, sz++) {
				l = min(l, R[A[j]]);
				r = max(r, R[A[j]]);
				if (r - l == sz)
					ret++;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
