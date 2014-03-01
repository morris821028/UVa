#include<stdio.h>
#include<stdlib.h>
#define Maxv 10000000
struct matrix {
	int C[1000], l;
}matrix[1001], pile[1001], map[1001];
int set[1001], used[1001];
int n, m, Ans;
int init(int n, int m) {
	int a;
	for(a = 1; a <= m; a++)
		pile[a].l = 0, set[a] = 0;
	for(a = 0; a < n; a++)
		map[a].l = 0, used[a] = 0;
}
int Build(int n) {
	int a, b, in1, in2, flag;
	for(a = 0; a < n; a++)
		for(b = a+1; b < n; b++) {
			in1 = 0, in2 = 0, flag = 0;
			while(in1 < matrix[a].l && in2 < matrix[b].l) {
				if(matrix[a].C[in1] < matrix[b].C[in2])	in1++;
				else if(matrix[a].C[in1] > matrix[b].C[in2])	in2++;
				else {flag = 1;break;}
			}
			if(flag) {
				map[a].C[map[a].l++] = b;
				map[b].C[map[b].l++] = a;
			}
		} 
} 
void DFS(int column, int k) {
	if(k >= Ans) return;
	if(column == m+1) {
		if(k < Ans) Ans = k;
		return;
	}
	if(set[column]) {
		DFS(column+1, k);
		return;
	}
	int a, b, t1 = pile[column].l, t2, flag;
	for(a = 0; a < t1; a++) {
		t2 = pile[column].C[a], flag = 0;
		if(used[t2]) continue;
		for(b = 0; b < matrix[t2].l; b++)
			set[matrix[t2].C[b]] = 1;
		for(b = 0; b < map[t2].l; b++)
			used[map[t2].C[b]]++;
		DFS(column+1, k+1);
		for(b = 0; b < matrix[t2].l; b++)
			set[matrix[t2].C[b]] = 0;
		for(b = 0; b < map[t2].l; b++)
			used[map[t2].C[b]]--;
	}
	return;
}
main() {
	int a, b, t, C = 0;
	/*freopen("in.txt", "rt", stdin);   
	freopen("out.txt", "w+t", stdout);*/
	while(scanf("%d %d", &n, &m) == 2) {
		init(n, m);
		int mark[1001] = {};
		for(a = 0; a < n; a++) {
			scanf("%d", &t);
			for(b = 0; b < t; b++)
				scanf("%d", &matrix[a].C[b]), mark[matrix[a].C[b]]++;
			pile[matrix[a].C[0]].C[pile[matrix[a].C[0]].l++] = a;
			matrix[a].l = t;
		}
		for(a = 1; a <= m; a++)
			if(mark[a] == 0) break;
		if(a != m+1)	{puts("No");continue;}
		Build(n);
		Ans = Maxv, DFS(1, 0);
		if(Ans == Maxv)	puts("No");
		else		printf("%d\n", Ans);
	}
	return 0;
}
