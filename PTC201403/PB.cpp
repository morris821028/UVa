#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;
int n, g[35][35];
int ret;
int used[35] = {};
int A[35], limit;
int H(int idx) {
	int cnt = 0;
	while(idx < n) {
		cnt += !used[idx];
		idx++;
	}
	return cnt;
}
void dfs(int idx, int ch) {
	if(ch + H(idx) < ret)
		return;
	int ok = 1;
	for(int i = 0; i < ch; i++) {
		int x = A[i], known = 0;
		for(int j = 0; j < n; j++) {
			if(used[j] == 1 && g[x][j] == 1)
				known++;
		}
		ok &= known >= 2;
	}
	for(int i = 0; i < ch; i++) {
		int x = A[i], unknown = 0;
		for(int j = 0; j < n; j++) {
			if(used[j] == 1 && g[x][j] == 0)
				unknown++;
		}
		ok &= unknown >= 2;
	}
	if(ok)	ret = max(ret, ch);
	if(idx == n)
		return;
	if(used[idx] == 0) {
		used[idx] = 1;
		A[ch] = idx;
		int known = 0, unknown = 0;
		for(int i = 0; i < n; i++) {
			if(used[i]) {
				if(g[idx][i])	known++;
				else			unknown++;
			}
		}
		if(known == 0) {
			for(int i = idx+1; i < n; i++) {
				if(g[idx][i] && used[i] == 0) {
					for(int j = i+1; j < n; j++) {
						if(g[idx][j] && used[j] == 0) {
							used[i] = used[j] = 1;
							A[ch+1] = i, A[ch+2] = j;
							if(unknown == 0) {
								for(int k = 0; k < n; k++)  {
									if(g[idx][k] == 0 && used[k] == 0)
									for(int l = k+1; l < n; l++) {
										if(g[idx][l] == 0 && used[l] == 0) {
											used[k] = used[l] = 1;
											A[ch+3] = k, A[ch+4] = l;
											dfs(idx+1, ch+5);
											used[k] = used[l] = 0;
										}
									}
								}
							} else if(unknown == 1){
								for(int k = 0; k < n; k++)  {
									if(g[idx][k] == 0 && used[k] == 0) {
										used[k] = 1;
										A[ch+3] = k;
										dfs(idx+1, ch+4);
										used[k] = 0;
									}
								}
							} else {
								dfs(idx+1, ch+3);
							} 
							used[i] = used[j] = 0;
						}
					}
				}
			}
		}
		else if(known == 1) {
			for(int i = idx+1; i < n; i++) {
				if(g[idx][i] && used[i] == 0) {
					used[i]  = 1;
					A[ch+1] = i;
					if(unknown == 0) {
						for(int k = 0; k < n; k++)  {
									if(g[idx][k] == 0 && used[k] == 0)
									for(int l = k+1; l < n; l++) {
										if(g[idx][l] == 0 && used[l] == 0) {
											used[k] = used[l] = 1;
											A[ch+2] = k, A[ch+3] = l;
											dfs(idx+1, ch+4);
											used[k] = used[l] = 0;
										}
									}
								}
							} else if(unknown == 1){
								for(int k = 0; k < n; k++)  {
									if(g[idx][k] == 0 && used[k] == 0) {
										used[k] = 1;
										A[ch+2] = k;
										dfs(idx+1, ch+3);
										used[k] = 0;
									}
								}
							} else {
								dfs(idx+1, ch+2);
							} 
					used[i]  = 0;
				}
			}
		} else {
			if(unknown == 0) {
								for(int k = 0; k < n; k++)  {
									if(g[idx][k] == 0 && used[k] == 0)
									for(int l = k+1; l < n; l++) {
										if(g[idx][l] == 0 && used[l] == 0) {
											used[k] = used[l] = 1;
											A[ch+1] = k, A[ch+2] = l;
											dfs(idx+1, ch+3);
											used[k] = used[l] = 0;
										}
									}
								}
							} else if(unknown == 1){
								for(int k = 0; k < n; k++)  {
									if(g[idx][k] == 0 && used[k] == 0) {
										used[k] = 1;
										A[ch+1] = k;
										dfs(idx+1, ch+2);
										used[k] = 0;
									}
								}
							} else {
								dfs(idx+1, ch+1);
							} 
		}
		used[idx] = 0;
	}
	dfs(idx+1, ch);
}
int main() {
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				scanf("%d", &g[i][j]);
			}
		}
		limit = 0;
		ret = 0;
		dfs(0, 0);
		printf("%d\n", ret);
	}
	return 0;
}
/*
5
1 1 0 1 1
1 1 1 0 0
0 1 1 1 0
1 0 1 1 1
1 0 0 1 1
6
1 1 0 0 1 1
1 1 1 0 0 0
0 1 1 1 0 1
0 0 1 1 1 1
1 0 0 1 1 1
1 0 1 1 1 1
*/
