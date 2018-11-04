#include <stdio.h>
#include "validMoveNum.h"
#include "nextMove.h"

int main() {
	int n, m;
	static int kx[10000], ky[10000];
	static int visited[100][100] = {};
	static int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
	static int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &kx[i], &ky[i]);
		visited[kx[i]][ky[i]] = i*10000;
	}

	for (int it = 1, valid = m; valid; it++) {
        for (int i = 1; i <= m; i++) {
            if (kx[i] < 0)
                continue;
            int sel = nextMove(kx[i], ky[i], n, visited);
            if (sel == -1) {
                kx[i] = -1, valid--;
            } else {
                kx[i] += dx[sel], ky[i] += dy[sel];
                visited[kx[i]][ky[i]] = i*10000 + it;
            }
        }
    }
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d%c", visited[i][j], " \n"[j==n-1]);
    }
	return 0;
}
