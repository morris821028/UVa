#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
	long long DP[301][301] = {};
	int i, j, k;
	char str[1000];
	DP[0][0] = 1;
	for(i = 1; i <= 300; i++) {
		for(j = i; j <= 300; j++) {
			for(k = 1; k <= j; k++)
				DP[j][k] += DP[j-i][k-1];
		}
	}
	while(gets(str)) {
		stringstream sin(str);
		int num[3], n = 0;
		while(sin >> num[n])
			n++;
		int p, q;
		if(n == 1)	
			p = 0, q = num[0];
		else if(n == 2)
			p = 0, q = num[1];
		else
			p = num[1], q = num[2];
		n = num[0];
		if(q > n)	q = n;
		long long ans = 0;
		for(i = p; i <= q; i++)
			ans += DP[n][i];
		printf("%lld\n", ans);
	}
    return 0;
}
