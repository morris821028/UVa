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
	char buf[105];
	sprintf(buf, "%d", n);
	int len = strlen(buf);
	int prev = 0, suffix;
	calc(mpow(10, len-1)-1, cnt);
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
		for(int j = i == 0; j < 10; j++) {
			if(j == d)	continue;
			if(j < d) {
				if(prev > 0) {
					cnt[j] += (prev - prev10/10 + 1) * mpow(10, len-i-1);
				} else {
					cnt[j] += mpow(10, len-i-1);
				}
			} else {
				if(prev > 0 && prev - prev10/10 > 0) {
					cnt[j] += (prev - prev10/10) * mpow(10, len-i-1);
				}
			}
		}
		prev10 *= 10;
		prev = prev * 10 + d;
	}
}
void brute(int n) {
	int cnt[10] = {};
	char buf[105];
	for(int i = 1; i <= n; i++) {
		sprintf(buf, "%d", i);
		for(int j = 0; buf[j]; j++)
			cnt[buf[j]-'0']++;
	}
	for(int i = 0; i < 10; i++)
		printf("%d ", cnt[i]);
	puts("");
}
int main() {	
	int l, r;
	while(scanf("%d %d", &l, &r) == 2 && l) {
		if(l == 0 && r == 0)
			break;
		if (l > r)	swap(l, r);
		int A[10] = {}, B[10] = {};
		calc(l-1, A);
		calc(r, B);
		for(int i = 0; i < 10; i++)
			printf("%d%c", B[i] - A[i], i ==  9 ? '\n' : ' ');
		
	}
	return 0;
}
