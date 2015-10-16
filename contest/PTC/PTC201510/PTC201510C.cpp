#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
struct State {
	int A, B, n1, n2, n3, x, y;
	State(int a = 0, int b = 0, int c = 0, int d = 0, 
		int e = 0, int f = 0, int g = 0):
		A(a), B(b), n1(c), n2(d), n3(e), x(f), y(g) {
	}
	bool operator<(const State &u) const {
		if (B != u.B)	return B < u.B;
		if (A != u.A)	return A > u.A;
		if (x != u.x)	return x < u.x;
		if (y != u.y)	return y < u.y;
		if (n1 != u.n1)	return n1 < u.n1;
		if (n2 != u.n2)	return n2 < u.n2;
		return n3 < u.n3;
	}
};
char g[16][16];
set<State> S;
int bfs(int n1, int n2, int n3) {
	S.clear();
	int a, b;
	set<State> Q;
	State u;
	Q.insert(State(100, 777, n1, n2, n3));
	S.insert(State(100, 777, n1, n2, n3));
	while (!Q.empty()) {
		u = *Q.begin(), Q.erase(Q.begin());
		if (u.x + 1 < 7) {
			int tA = u.A, tB = u.B;
			if (g[u.x+1][u.y] == '-')
				tA -= n2;
			else
				tB -= n2;
			if (tB <= 0)	return 1;
			if (tA > 0) {
				State v = State(tA, tB, 7-n2, n1, n3, u.x+1, u.y);
				if (S.count(v) == 0) {
					S.insert(v);
					Q.insert(v);
				}
			}
		}
		if (u.x - 1 >= 0) {
			int tA = u.A, tB = u.B;
			if (g[u.x-1][u.y] == '-')
				tA -= 7-n2;
			else
				tB -= 7-n2;
			if (tB <= 0)	return 1;
			if (tA > 0) {
				State v = State(tA, tB, n2, 7-n1, n3, u.x-1, u.y);
				if (S.count(v) == 0) {
					S.insert(v);
					Q.insert(v);
				}
			}
		}
		if (u.y + 1 < 7) {
			int tA = u.A, tB = u.B;
			if (g[u.x][u.y+1] == '-')
				tA -= n3;
			else
				tB -= n3;
			if (tB <= 0)	return 1;
			if (tA > 0) {
				State v = State(tA, tB, 7-n3, n2, n1, u.x, u.y+1);
				if (S.count(v) == 0) {
					S.insert(v);
					Q.insert(v);
				}
			}
		}
		if (u.y - 1 >= 0) {
			int tA = u.A, tB = u.B;
			if (g[u.x][u.y-1] == '-')
				tA -= 7-n3;
			else
				tB -= 7-n3;
			if (tB <= 0)	return 1;
			if (tA > 0) {
				State v = State(tA, tB, n3, n2, 7-n1, u.x, u.y-1);
				if (S.count(v) == 0) {
					S.insert(v);
					Q.insert(v);
				}
			}
		}
	}
	return 0;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n1, n2, n3;
		scanf("%d %d %d", &n1, &n2, &n3);
		for (int i = 0; i < 7; i++)
			scanf("%s", g[i]);
		int ret = 0;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				if (g[i][j] == '+' && g[i+1][j] == '+')
					ret = 1;
				if (g[i][j] == '+' && g[i][j+1] == '+')
					ret = 1;
			}
		}
//		int ret = bfs(n1, n2, n3);	// WTF
		
		puts(ret ? "yes" : "no");
	}
	return 0;
}
