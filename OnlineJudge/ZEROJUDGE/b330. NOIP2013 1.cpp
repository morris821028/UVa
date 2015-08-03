#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int mpow(int n, int m) {
	int ret = 1;
	for(int i = 1; i <= m; i++)
		ret *= n;
	return ret;
}
void calc(int n, int cnt[]) {
	if(n <= 0)
		return;
	//printf("%d\n", n);
	char buf[105];
	sprintf(buf, "%d", n);
	int len = strlen(buf);
	int prev = 0, suffix;
	calc(mpow(10, len-1)-1, cnt);
	//for(int i = 0; i < 10; i++)
	//	cnt[i] = 0;
	int prev10 = 1;
	for(int i = 0; i < len; i++) {
		int d = buf[i] - '0';
		sscanf(buf+i+1, "%d", &suffix);
		
		if(i != len-1)
			cnt[d] += suffix + 1;
		else
			cnt[d]++;
		if(i != 0)
			cnt[d] += (prev - prev10/10) * mpow(10, len-i-1);
	//	pritnf("%d \n", );
	//	puts("");
		for(int j = i == 0; j < 10; j++) {
			if(j == d)	continue;
			if(j < d) {
				if(prev > 0) {
					cnt[j] += (prev - prev10/10 + 1) * mpow(10, len-i-1);
					//printf("%d %d\n", j, (prev - prev10/10 + 1) * mpow(10, len-i-2));
				} else {
					cnt[j] += mpow(10, len-i-1);
					//printf("%d %d\n", j, mpow(10, len-i-1));
				}
			} else {
				if(prev > 0 && prev - prev10/10 > 0) {
					cnt[j] += (prev - prev10/10) * mpow(10, len-i-1);
					//printf("%d %d\n", j, (prev - prev10/10 + 1) * mpow(10, len-i-2));
				}
			}
		}
		prev10 *= 10;
		prev = prev * 10 + d;
	}
	/*for(int i = 0; i < 10; i++)
		printf("%d ", cnt[i]);
	puts("");*/
}
int main() {
	int n, x;
	while(scanf("%d %d", &n, &x) == 2) {
		int A[10] = {};
		calc(n, A);
		printf("%d\n", A[x]);		
	}
	return 0;
}
