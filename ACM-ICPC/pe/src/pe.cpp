//============================================================================
// Name        : pe.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
#define oo 2147483647
using namespace std;
int Map[1000][1000];
int Max(int x, int y) {
	return x > y ? x : y;
}
int Min(int x, int y) {
	return x < y ? x : y;
}
int solve(int st, int ed, int n) {
	int i, j;
	int V[1000], Used[1000];
	for(i = 0; i < n; i++)
		V[i] = -oo, Used[i] = 0;
	V[st] = 0, Used[st] = 1;
	for(i = 0; i < n; i++) {
		int tn = st, next = oo;
		for(j = 0; j < n; j++)
			if(next > V[j] && V[j] != -oo && Used[j] == 0)
				next = V[j], tn = j;
		Used[tn] = 1;
		for(j = 0; j < n; j++) {
			if(V[j] != -oo)
				V[j] = Min(Max(V[tn], Map[tn][j]), V[j]);
			else
				V[j] = Max(V[tn], Map[tn][j]);
		}
	}
	return V[ed];
}
int main() {
	freopen("pe.in", "r", stdin);
	int n, X[1000], Y[1000], i, j;
	while(scanf("%d", &n) == 1 && n) {
		int st, ed;
		for(i = 0; i < n; i++)
			scanf("%d %d", &X[i], &Y[i]);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				Map[i][j] = (X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]);
		scanf("%d %d", &st, &ed);
		printf("%d\n", solve(st-1, ed-1, n));
	}
	return 0;
}/*
4
0 0
1 9
8 2
10 10
1 4
5
0 0
8 2
3 4
8 7
10 10
1 5
0
*/
