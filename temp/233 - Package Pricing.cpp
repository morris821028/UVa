#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <map>
#include <queue>
using namespace std;

struct COMB {
	int label, supply[4];
	double price;
	void init() {
		memset(supply, 0, sizeof(supply));
	}
	void print() {
		printf("%d %lf %d %d %d %d\n", label, price, supply[0], supply[1], supply[2], supply[3]);
	}
	bool operator<(const COMB &p) const {
		return label < p.label;
	}
} products[64];
int n, q, need[16];
int mnCnt[64], path[64];
double mnCost;
double dp[1048576];
int dpChoose[1048576][2];
int row[4];
int getIndex(int A[]) {
	int v = 0;
	for (int j = 0; j < 4; j++)
		v += A[j] * row[j];
	return v;
}
void bfs() {
	row[0] = (need[3]+1)*(need[2]+1)*(need[1]+1);
	row[1] = (need[3]+1)*(need[2]+1);
	row[2] = need[3]+1;
	row[3] = 1;
	int A[4], B[4], u, v, mxState = getIndex(need);
	for (int i = 0; i <= mxState; i++)
		dp[i] = 1e+50, dpChoose[i][0] = dpChoose[i][1] = -1;
	dpChoose[0][1] = -1, dp[0] = 0;
	for (int p = 0; p <= mxState; p++) {
		u = p;
		for (int i = 0; i < 4; i++)
			A[i] = u / row[i], u %= row[i];
		u = p;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 4; j++)
				B[j] = min(A[j] + products[i].supply[j], need[j]);
			v = getIndex(B);
			if (dp[v] > dp[u] + products[i].price)
				dp[v] = dp[u] + products[i].price, dpChoose[v][0] = i, dpChoose[v][1] = u;
		}
	}
	memset(mnCnt, 0, sizeof(mnCnt));
	for (int p = mxState; p != -1; p = dpChoose[p][1])
		mnCnt[dpChoose[p][0]]++;		
	mnCost = dp[mxState];
}
int main() {
	char line[1024];
	string token;
	int cnt = 0;
	while (scanf("%d", &n) == 1) {
		while (getchar() != '\n');
		
		for (int i = 0; i < n; i++) {
			products[i].init();
			gets(line);
			stringstream sin(line);
			sin >> products[i].label >> products[i].price;
			while (sin >> token >> cnt)
				products[i].supply[token[0] - 'a'] += cnt;
		}
		sort(products, products + n);
		gets(line);
		sscanf(line, "%d", &q);
		for (int i = 0; i < q; i++) {
			memset(need, 0, sizeof(need));
			gets(line);
			stringstream sin(line);
			while (sin >> token >> cnt)
				need[token[0] - 'a'] += cnt;
			bfs();
			printf("%d:%8.2lf", i + 1, mnCost);
			for (int j = 0; j < n; j++) {
				if (mnCnt[j]) {
					printf(" %d", products[j].label);
					if (mnCnt[j] > 1)
						printf("(%d)", mnCnt[j]);
				}
			}
			puts("");
		}
		puts("");
	}
	return 0;
}
