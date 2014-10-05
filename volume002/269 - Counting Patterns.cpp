#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <set>
#include <assert.h>
using namespace std;
set<int> S;
int n, m, path[20], way[131072][20], ways;

bool cmp (int l[], int r[]) {
    for (int i = 0; i < n; i++)
        if (l[i] != r[i])
            return l[i] > r[i];
    return false;
}

void check (int a[]) {
    int b[32];

    for (int i = 0; i < n; i++)
        b[i] = b[i+n] = a[i];
    for (int i = 0; i < n; i++)
        if (b[i] == a[0] && cmp(b+i, a))
            return;

    for (int i = 0; i < 2 * n; i++)
        b[i] = -b[i];
    for (int i = 0; i < n; i++)
        if (b[i] == a[0] && cmp(b+i, a))
            return;

    for (int i = 0; i < n; i++)
        swap(b[i], b[2*n-i-1]);
    for (int i = 0;  i < n; i++)
        if (b[i] == a[0] && cmp(b+i, a))
            return;

    for (int i = 0; i < 2 * n; i++)
        b[i] = -b[i];
    for (int i = 0; i < n; i++)
        if (b[i] == a[0] && cmp(b+i, a))
            return;

    memcpy(way[ways++], a, sizeof(int) * n);
}
void dfs(int idx, int sum) {
	if (abs(sum) > abs((n - idx) * path[0]))
		return;
	if (idx == n) {
		if (sum == 0) 
			check(path);
		return;
	}
	if (idx == 0) {
		for (int i = 1; i <= m; i++) {
			path[idx] = i;
			dfs(idx+1, sum + i);
		}
	} else {
		for (int i = -abs(path[0]); i <= abs(path[0]); i++) {
			path[idx] = i;
			dfs(idx+1, sum + i);
		}
	}
}
int main() {
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		ways = 1;
		dfs(0, 0);
		if (cases++) 
			puts("");
		printf("%d\n", ways);
		for (int i = 0; i < ways; i++) {
			printf("(%d", way[i][0]);
			for (int j = 1; j < n; j++)
			    printf(",%d", way[i][j]);
			puts(")");
		}
	}
	return 0;
}
/*
1 0
1 1
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
2 0
2 1
2 2
2 3
2 4
2 5
2 6
2 7
2 8
2 9
3 0
3 1
3 2
3 3
3 4
3 5
3 6
3 7
3 8
4 0
4 1
4 2
4 3
4 4
4 5
4 6
4 7
5 0
5 1
5 2
5 3
5 4
5 5
5 6
6 0
6 1
6 2
6 3
6 4
6 5
7 0
7 1
7 2
7 3
7 4
8 0
8 1
8 2
8 3
9 0
9 1
9 2
10 0
10 1
11 0
*/
