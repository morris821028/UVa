#include<stdio.h>
#include<string.h>
int main() {
	int sum[101], i, s, n;
	memset(sum, 0, sizeof(sum));
	while(scanf("%d", &s) == 1) {
		if(s == -1)	break;
		scanf("%d", &n), sum[s] += n;
	}
	while(scanf("%d", &s) == 1) {
		if(s == -1)	break;
		scanf("%d", &n), sum[s] += n;
	}
	for(i = 0; i <= 100; i++)
		if(sum[i])
			printf("%d %d\n", i, sum[i]);
	return 0;
}
