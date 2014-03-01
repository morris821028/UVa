#include<stdio.h>
#include<stdlib.h>
int cmp(const void *i, const void *j) {
	return *(int *)i - *(int *)j;
}
int main() {
	int T, S[21], i, n;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(i = 1; i <= 4; i++)
			scanf("%d", &S[i]);
		for(i = 5; i <= n; i++)
			S[i] = S[i-4] + S[i-1];
		qsort(S+1, n, sizeof(int), cmp);
		printf("%d\n", S[n/2+1]);
	}
	return 0;
}
