#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <map>
#include <iostream>
using namespace std;
// learn: http://blog.csdn.net/jiangshibiao/article/details/28661223		
#define MAXN 105
#define INF 1e+6
#define eps 1e-9
double R[MAXN][MAXN] = {}, V[MAXN] = {}; // R: resist, V: voltage
double f[MAXN][MAXN] = {}; // function need solved;
int main() {
	int N, A, B;
	int x, y, l;
	int cases = 0;
	double w;
	char s1[105], s2[105];
	while(scanf("%d %d %d", &N, &A, &B) == 3) {
		if(N == 0)
			break;
		map<int, int> label;
		l = label[A];
		if(l == 0)	label[A] = label.size();
		A = label[A];
		
		l = label[B];
		if(l == 0)	label[B] = label.size();
		B = label[B];
		
		memset(R, 0, sizeof(R));
		memset(V, 0, sizeof(V));
		memset(f, 0, sizeof(f));
		vector<double> g[MAXN][MAXN];
		for(int i = 0; i < N; i++) {
			scanf("%d %d %lf", &x, &y, &w);
			
			l = label[x];
			if(l == 0)	label[x] = label.size();
			x = label[x];
			
			l = label[y];
			if(l == 0)	label[y] = label.size();
			y = label[y];
			
			g[x][y].push_back(w);
			g[y][x].push_back(w);
		}
		N = label.size();

		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				if(g[i][j].size()) {
					double r = 0;
					for(int k = 0; k < g[i][j].size(); k++) {
						r += 1.0 / g[i][j][k];
					}
					R[i][j] = 1.0 / r;
				}
			}
		}
		V[A] = INF, V[B] = 0;
		for(int i = 1; i <= N; i++) {
			if(i == A)	continue;
			if(i == B)	continue;
			if(R[i][A] > 0)
				f[i][i] -= 1.0 / R[i][A], f[i][N + 1] -= V[A] / R[i][A];
			if(R[i][B] > 0)
				f[i][i] -= 1.0 / R[i][B], f[i][N + 1] -= V[B] / R[i][B];
			for(int j = 1; j <= N; j++) {
				if(R[i][j] > 0 && i != j && j != A && j != B)
					f[i][j] = 1.0 / R[i][j], f[i][i] -= 1.0 / R[i][j];
			}
		}
		// Gaussian Elimination
		for(int i = 1; i <= N; i++) {
			int k = i;
			for(int j = i + 1; j <= N; j++)
				if(f[j][i] > 0)
					k = j;
			if(fabs(f[k][i]) < eps)
				continue;
			for(int j = 1; j <= N + 1; j++)
				swap(f[i][j], f[k][j]);
			for(int j = 1; j <= N; j++) {
				if(i == j)	continue;
				for(int k = N + 1; k >= i; k--)
					f[j][k] = f[j][k] - f[j][i] / f[i][i] * f[i][k];
			}
		}

		for(int i = 1; i <= N; i++) {
			if(i == A)	continue;
			if(i == B)	continue;
			if(fabs(f[i][i]) > eps)
				V[i] = f[i][N + 1] / f[i][i];
		}
		
		double IB = 0;
		for(int i = 1; i <= N; i++)
			if(R[i][B] > 0)
				IB += V[i] / R[i][B];
		if(fabs(IB) < eps)
			printf("Case %d: %.2lf Ohms\n", ++cases, 0);
		else
			printf("Case %d: %.2lf Ohms\n", ++cases, (V[A] - V[B]) / IB);
	}
	return 0;
}
