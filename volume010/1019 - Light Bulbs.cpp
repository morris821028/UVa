#include <bits/stdc++.h> 
using namespace std;

const int MAXB = 512;
void trans(char s[], int d[]) {
	int n = strlen(s);
	int v[MAXB] = {};
	for (int i = 0; i < n; i++)
		v[i] = s[n-1-i]-'0';
	memset(d, 0, sizeof(v));
	for (int i = 0; ; i++) {
		int m = 0, zero = 1;
		for (int j = n-1; j >= 0; j--) {
			m = m*10 + v[j];
			zero &= v[j] == 0;
			v[j] = m>>1, m &= 1;
		}
		if (zero)
			break;
		d[i] = m;
	}
}
int len(int d1[], int d2[]) {
	for (int i = MAXB-1; i >= 0; i--) {
		if (d1[i] || d2[i])
			return i+1;
	}
	return 1;
}
		
int st_d[MAXB] = {}, ed_d[MAXB] = {};
int path[MAXB] = {};
int ret[MAXB] = {}, has = 0;
void press(int idx, int n) {
	for (int i = -1; i <= 1; i++) {
		if (idx+i >= 0 && idx+i <= n)
			st_d[idx+i] = !st_d[idx+i];
	}
}
int cmp(int path[], int ret[], int n) {
	for (int i = n-1; i >= 0; i--) {
		if (path[i] > ret[i])
			return 1;
		if (ret[i] > path[i])
			return -1;
	}
	return 0;
}
void dfs(int idx, int n) {
	if (idx == n) {
		if (st_d[idx-1] != ed_d[idx-1])
			return;
		if (!has || cmp(path, ret, n) < 0) {
			memcpy(ret, path, sizeof(ret[0])*n);
			has = 1;
		}
		return;
	}
	if (idx > 0) {
		if (st_d[idx-1] != ed_d[idx-1]) {
			path[idx] = 1;
			press(idx, n);
			dfs(idx+1, n);
			press(idx, n);
		} else {
			path[idx] = 0;
			dfs(idx+1, n);
		}
	} else {
		path[idx] = 0;
		dfs(idx+1, n);
		path[idx] = 1;
		press(idx, n);
		dfs(idx+1, n);
		press(idx, n);
	}
}
void output(int s[], int n) {
	int ret[MAXB] = {};
	for (int i = n-1; i >= 0; i--) {
		for (int j = 0, c = s[i]; j < n; j++) {
			ret[j] = (ret[j]<<1) + c;
			c = ret[j]/10, ret[j] %= 10;
		}
	}

	for (int i = n-1; i >= 0; i--) {
		if (i == 0 || ret[i]) {
			while (i >= 0) {
				printf("%d", ret[i]);
				i--;
			}
		}
	}
	puts("");
}
int main() {
	int cases = 0;
	char st[128], ed[128];
	while (scanf("%s %s", st, ed) == 2) {
		if (!strcmp(st, "0") && !strcmp(ed, "0"))
			break;
		if (cases)
			puts("");

		int sw[MAXB] = {};
		trans(st, st_d);
		trans(ed, ed_d);
		int n = len(st_d, ed_d);

		has = 0;
		dfs(0, n);

		printf("Case Number %d: ", ++cases);
		if (!has)
			puts("impossible");
		else
			output(ret, n);
	}
	return 0;
}
/*
12 16
1 1
3 0
30 5
7038312 7427958190
4253404109 657546225
*/
