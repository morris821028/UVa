#include <bits/stdc++.h>
using namespace std;

int areaTri(double a, double b, double c) {
	double s = (a+b+c)/2.f;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}

int validTri(int a, int b, int c) {
	return a < b+c && b < a+c && c < b+a;
}
int n, A[512], C[512][2], ret, cn;
int D[3];
int pickRect() {
	int p = -1;
	for (int i = cn-1; i >= 0; i--) {
		if (C[i][1] >= 4 && p == -1)
			return C[i][0]*C[i][0];
		if (C[i][1] >= 2) {
			if (p != -1)
				return p * C[i][0];
			p = C[i][0];
		}
	}
	return 0;
}
void dfs(int idx, int i) {
	if (idx == 3) {
		if (!validTri(D[0], D[1], D[2]))
			return ;
		int tmp = areaTri(D[0], D[1], D[2])+pickRect();
		ret = max(ret, tmp);
		return ;
	}
	if (i == cn)
		return ;
	for (int j = 1; j <= C[i][1] && idx+j <= 3; j++) {
		if (j == 1)	
			D[idx] = C[i][0], C[i][1]--;
		else if (j == 2) 
			D[idx] = D[idx+1] = C[i][0], C[i][1] -= 2;
		else
			D[idx] = D[idx+1] = D[idx+2] = C[i][0], C[i][1] -= 3;
		dfs(idx+j, i+1);
		if (j == 1)	
			C[i][1]++;
		else if (j == 2) 
			C[i][1] += 2;
		else
			C[i][1] += 3;
	}
	dfs(idx, i+1);
}
int main() {
	int cases = 0;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		
		int B[512] = {}, M[512];
		for (int i = 0; i < n; i++)
			B[A[i]]++;
		cn = 0;
		for (int i = 0; i <= 256; i++) {
			if (B[i]) {
				M[i] = cn;
				C[cn][0] = i, C[cn][1] = B[i], cn++;
			}
		}
		ret = pickRect();
		dfs(0, 0);
		printf("%d\n", ret);
	}
	return 0;
}
/*
3
3
4
5
7
1
4
1
2
3
2
3
9
10
10
10
10
10
10
10
10
10
3
1
1
8
*/

