#include <stdio.h> 
#include <queue>
#include <algorithm>
using namespace std;
#define MAXN 512

int g[MAXN][MAXN];
struct Position {
	int x, y, height;
	Position(int a = 0, int b = 0, int c = 0):
		x(a), y(b), height(c) {}
	bool operator<(const Position &a) const {
		return height > a.height;
	}
};
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
vector<Position> D;
int n, m, d;
int dp[MAXN][MAXN]; // search heightest
int bfs(int x, int y, int height) {
	if (dp[x][y] != -1)	return 0;
	queue<int> X, Y;
	int ok = 1, same = 1, tx, ty;
	X.push(x) , Y.push(y), dp[x][y] = height;
	while (!X.empty()) {
		x = X.front(), X.pop();
		y = Y.front(), Y.pop();
		for (int i = 0; i < 4; i++) {
			tx = x + dx[i], ty = y + dy[i];
			if (tx < 0 || ty < 0 || tx >= n || ty >= m)
				continue;
			if (g[tx][ty] <= height - d)
				continue;
			if (dp[tx][ty] > height) {
				ok = 0;
				continue;
			}
			if (dp[tx][ty] == height)
				continue;
			if (g[tx][ty] == height)	same++;
			dp[tx][ty] = height;
			X.push(tx), Y.push(ty);
		}
	}
	return ok ? same : 0;
}
void findSummit() {
	D.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			D.push_back(Position(i, j, g[i][j]));
			dp[i][j] = -1;
		}
	}
	sort(D.begin(), D.end());
	
	int ret = 0;
	for (int i = 0; i < D.size(); i++) {
		ret += bfs(D[i].x, D[i].y, D[i].height);
	}
	printf("%d\n", ret);
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
	int testcase;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d %d %d", &n, &m, &d);
		ReadInt(&n);
		ReadInt(&m);
		ReadInt(&d);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
//				scanf("%d", &g[i][j]);
				ReadInt(&g[i][j]);
		findSummit();
	}
	return 0;
}
/*
999
2 2 0
9 9
9 9 
1
6 10 2
0 0 0 0 0 0 0 0 0 0
0 1 2 1 1 1 1 0 1 0
0 2 1 2 1 3 1 0 0 0
0 1 2 1 3 3 1 1 0 0
0 2 1 2 1 1 1 0 2 0
0 0 0 0 0 0 0 0 0 0
*/
