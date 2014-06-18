#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define oo 2147483647
int map[1000][1000], Mt[1000];
int Used[1000], Time[1000], Ans;
int gcd(int x, int y) {
	int tmp;
	while(x%y) {
		tmp = x, x = y, y = tmp%y;
	}
	return y;
}
int DFS(int T, int now, int start) {
	int last = oo, i, tmp, flag = 0, ttry = 0;
	Time[now] = T;
	for(i = 0; i < Mt[now]; i++) {
		if(Used[map[now][i]] == 0) {
			Used[map[now][i]] = 1;
			tmp = DFS(T+1, map[now][i], 0);
			if(tmp >= T)	flag = 1;
			last = tmp < last ? tmp : last;
			ttry++;
		} else {
			tmp = Time[map[now][i]];
			last = tmp < last ? tmp : last;
		}
	}
	if(start == 1) {
		if(ttry > 1)
			Ans++;
		printf("%d\n", now);
	} else { 
		Ans += flag;
		flag != 0 && printf("%d\n", now);
	} 
	return last;
}
int main() {
	int T, i, j, A[1001], n, tmp;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		memset(Mt, 0, sizeof(Mt));
		memset(Used, 0, sizeof(Used));
		memset(Time, 0, sizeof(Time));
		Ans = 0;
		for(i = 0; i < n; i++)
			for(j = i+1; j < n; j++) {
				tmp = gcd(A[i], A[j]);
				if(tmp != 1) {
					map[i][Mt[i]++] = j;
					map[j][Mt[j]++] = i;
					printf("%d<->%d\n", i, j);
				}
			}
		for(i = 0; i < n; i++)
			if(Used[i] == 0) {
				Used[i] = 1, Time[i] = 1;
				DFS(1, i, 1);
			}
		printf("%d\n", Ans);
	}
	return 0;
}/*
2
7
2
6
21
77
143
187
221
*/
