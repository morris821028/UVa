#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define MAXN 4096
#define MAXD 20
#define MIND 10
#define MAXV 1664

typedef struct Pt {
	int x, y;
} Pt;
typedef struct Node {
	int idx;
	struct Node *next;
} Node;

static uint32_t hash(const int const *x, int n) {
    uint32_t ret = 0;
	for (int i = 0; i < n; i++)
        ret += x[i]*(i+1);
    return ret;
}

void radar(const Pt P[], int N, int D) {
	static Node nodes[MAXN*2];
	static Node *g[MAXV/MIND][MAXV/MIND];
	static int gc[MAXV/MIND][MAXV/MIND], cases = 0;
	static int rp[MAXN];
	int e = 0;
	cases++;
	
	/* mapping */
	for (int i = 0; i < N; i++) {
		int cx, cy;
		cx = P[i].x / D, cy = P[i].y / D;
		if (gc[cx][cy] != cases) {
			gc[cx][cy] = cases;
			g[cx][cy] = NULL;
		}
		nodes[e].idx = i, nodes[e].next = g[cx][cy];
		g[cx][cy] = &nodes[e], e++;
	}
	
	/* radar range */
	const int dx[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
	const int dy[] = {-1,  0,  1,-1, 0, 1,-1, 0, 1};
	for (int i = 0; i < N; i++) {
		int cx, cy, cnt = 0;
		cx = P[i].x / D, cy = P[i].y / D;
		for (int j = 0; j < 9; j++) {
			int tx = cx + dx[j];
			int ty = cy + dy[j];
			if (tx < 0 || ty < 0 || tx >= MAXV/MIND || ty >= MAXV/MIND)
				continue;
			if (gc[tx][ty] != cases)
				continue;
			for (Node *p = g[tx][ty]; p != NULL; p = p->next) {
				int idx = p->idx;
				int ddx = P[i].x - P[idx].x;
				int ddy = P[i].y - P[idx].y;
				if (ddx*ddx + ddy*ddy <= D*D) {
					cnt++;
//					printf("(%d, %d) %d %d %d %d\n", i, idx, P[i].x, P[i].y, P[idx].x, P[idx].y);
				}
			}
		}
//		printf("%d\n", cnt-1);
		rp[i] = cnt-1;
	}
//	puts("---");
	printf("%u\n", hash(rp, N));
}

int main() {
	int X, Y, D;
	int N, T;
	static Pt P[MAXN];
	while (scanf("%d %d %d", &X, &Y, &D) == 3) {
		scanf("%d %d", &N, &T);
		for (int i = 0; i < N; i++)
			scanf("%d %d", &P[i].x, &P[i].y);
		
		radar(P, N, D);
		for (int i = 1; i < T; i++) {
			for (int j = 0; j < N; j++) {
				int dx, dy;
				scanf("%d %d", &dx, &dy);
				P[j].x += dx, P[j].y += dy;
			}
			radar(P, N, D);
		}
	}
	return 0;
}
