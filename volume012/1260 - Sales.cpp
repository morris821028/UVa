#include <stdio.h>
#include <stdlib.h>
int main() {
	int T, n, A[1001];
	int i, j;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		int ans = 0, tmp;
		for(i = 0; i < n; i++) {
			scanf("%d", &tmp);
			for(j = i-1; j >= 0; j--)
				if(tmp < A[j])
					A[j+1] = A[j];
				else
					break;
			A[j+1] = tmp;
			ans += j+1;
		}
		printf("%d\n", ans);
	}
    return 0;
}
