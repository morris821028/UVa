#include<stdio.h>
main() {
	long long f[30001] = {0, 1}, g[30001] = {0, 1}, a;
	for(a = 2; a < 30001; a++)	f[a] = a + f[a-1], g[a] = f[a] + g[a-1];
	while(scanf("%lld", &a) == 1) 
		printf("%lld %lld\n", f[a], g[a]);
	return 0;
}
