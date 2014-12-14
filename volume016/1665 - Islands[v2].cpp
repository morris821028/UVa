#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm> 
using namespace std;

#define MAXN 1024
int g[MAXN][MAXN], h[131072], out[131072];
int parent[MAXN * MAXN], weight[MAXN * MAXN];

struct Pos {
	int x, y, h;
	Pos(int a = 0, int b = 0, int c = 0):
		x(a), y(b), h(c) {}
	bool operator<(const Pos &a) const {
		return h > a.h;
	}
};

int findp(int x) {
	return parent[x] == x ? x : parent[x] = findp(parent[x]);
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

Pos D[MAXN * MAXN], TMP[MAXN * MAXN];
void RadixSort(Pos *A, Pos *B, int n) {
    int a, x, d, C[256];
    Pos *T;
    for(x = 0; x < 4; x++) {
        d = x * 8;
        for(a = 0; a < 256; a++)     	C[a] = 0;
        for(a = n-1; a >= 0; a--)      	C[(A[a].h>>d)&255]++;
        for(a = 256 - 2; a >= 0; a--)   C[a] += C[a+1];
        for(a = n-1; a >= 0; a--)   	B[--C[(A[a].h>>d)&255]] = A[a];
        T = A, A = B, B = T;
    }    
}
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
	const int dx[] = {0, 0, 1, -1};
	const int dy[] = {1, -1, 0, 0};
	int testcase, n, m, q, tx, ty;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d %d", &n, &m);
		ReadInt(&n);
		ReadInt(&m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
//				scanf("%d", &g[i][j]);
				ReadInt(&g[i][j]);
//		scanf("%d", &q);
		ReadInt(&q);
		for (int i = 0; i < q; i++)
//			scanf("%d", &h[i]);
			ReadInt(&h[i]);
		
		int didx = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				D[didx++] = Pos(i, j, g[i][j]);
			}
		}
		RadixSort(D, TMP, n*m);
		int idx = 0, nm = n*m, sum = 0;
		Pos u;
		for (int i = nm; i >= 0; i--)
			parent[i] = i, weight[i] = 1;
		for (int i = q - 1; i >= 0; i--) {
			while (idx < nm && D[idx].h > h[i]) {
				sum++;
				u = D[idx++];
//				printf("add %d %d - %d\n", u.x, u.y, u.h);
				for (int j = 0; j < 4; j++) {
					tx = u.x + dx[j], ty = u.y + dy[j];
					if (tx < 0 || ty < 0 || tx >= n || ty >= m)
						continue;
					if (g[tx][ty] > h[i]) {
						sum -= joint(u.x * m + u.y, tx * m + ty);
					}
				}
			}
			out[i] = sum;
//			printf("%d\n", sum);
		}
		for (int i = 0; i < q; i++)
			printf("%d ", out[i]);
		puts("");
	}
	return 0;
}
