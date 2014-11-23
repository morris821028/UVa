#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define MAXN 65536
#define MAXM 65536
#define MAXQ 65536

int parent[MAXN], weight[MAXN];
int findp(int x) {
	return parent[x] == x ? x : (parent[x] = findp(parent[x]));
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x == y)	return 0;
	if (weight[x] > weight[y])
		weight[x] += weight[y], parent[y] = x;
	else
		weight[y] += weight[x], parent[x] = y;
	return 1;
}

int ex[MAXM], ey[MAXM], exists[MAXM];
char cmd[MAXQ][8];
int cmdx[MAXQ];
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout); 
	int n, m, q;
    while (scanf("%d %d", &n, &m) == 2) {
    	for (int i = 0; i < m; i++) { 
    		scanf("%d %d", &ex[i], &ey[i]);
    		ex[i]--, ey[i]--;
    		exists[i] = 1;
    	} 
    	scanf("%d", &q);
    	for (int i = 0; i < q; i++) {
    		scanf("%s %d", &cmd[i], &cmdx[i]);
    		cmdx[i]--;
    		if (cmd[i][0] == 'D')
    			exists[cmdx[i]] = 0;
    	}
    	
    	for (int i = 0; i < n; i++)
    		parent[i] = i, weight[i] = 1;
    	for (int i = 0; i < m; i++) {
    		if (exists[i] == 1)
    			joint(ex[i], ey[i]);
    	}
    	int ret[MAXQ], rt = 0;
    	for (int i = q - 1; i >= 0; i--) {
    		if (cmd[i][0] == 'Q')
    			ret[rt++] = weight[findp(cmdx[i])];
    		else
    			joint(ex[cmdx[i]], ey[cmdx[i]]);
    	}
    	for (int i = rt - 1; i >= 0; i--)
    		printf("%d\n", ret[i]);
    }
    return 0;
}
