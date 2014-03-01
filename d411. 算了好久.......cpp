#include<stdio.h>
main() {
	char S[10001];
	int a, N, s2[10]={1};
	for(a = 1; a < 10;s2[a]=s2[a-1]*2,a++);
	while(scanf("%s %d", S, &N) == 2) {
		int t = S[0]-'0';
		for(a = 1; S[a]; a++) {
			t = t*10 + S[a]-'0';
			t %= s2[N];
		}
		if(t)	printf("可惡!!算了這麼久%s竟然無法被2的%d次整除\n", S, N);
		else	printf("YA!!終於算出%s可被2的%d次整除了!!\n", S, N);
	}
	return 0;
}
