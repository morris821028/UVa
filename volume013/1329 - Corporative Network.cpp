#include <stdio.h> 
#include <stdlib.h>
#include <algorithm>
using namespace std;

int parent[32767], dist[32767];
int find(int x) {
	if (x == parent[x])	return x;
	int p = find(parent[x]);
	dist[x] += dist[parent[x]];
	return parent[x] = p;
}
int main() {
	int testcase, n;
	int x, y;
	char cmd[10];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			parent[i] = i, dist[i] = 0;
		while (scanf("%s", cmd) == 1 && cmd[0] != 'O') {
			if (cmd[0] == 'E') {
				scanf("%d", &x);
				find(x);
				printf("%d\n", dist[x]);
			} else {
				scanf("%d %d", &x, &y);
				parent[x] = y;
				dist[x] = abs(x - y)%1000;
			}
		}
	}
	return 0;
}
