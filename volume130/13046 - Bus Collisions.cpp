#include <bits/stdc++.h>
using namespace std;
struct Pt {
	int x, y;
	Pt(int x = 0, int y = 0): x(x), y(y) {
	}
	int dist(Pt u) {
		return abs(x - u.x) + abs(y - u.y);
	}
	bool operator==(const Pt &u) const {
		return x == u.x && y == u.y;
	}
	Pt operator-(const Pt &u) const {
		return Pt(x - u.x, y - u.y);
	}
	Pt operator+(const Pt &u) const {
		return Pt(x + u.x, y + u.y);
	}
};
int main() {
	int testcase, cases = 0;
	int N[2], x, y;
	Pt R[2][64];
	scanf("%d", &testcase);
	while (testcase--) {
		int Len[2] = {};
		for (int i = 0; i < 2; i++) {
			scanf("%d", &N[i]);
			for (int j = 0; j < N[i]; j++) {
				scanf("%d %d", &x, &y);
				R[i][j] = Pt(x, y);
			}
			for (int j = 0; j < N[i]; j++)
				Len[i] += R[i][j].dist(R[i][(j+1)%N[i]]);
		}
		
		printf("Case %d: ", ++cases);
		
		int simT = Len[0]/__gcd(Len[0], Len[1])*Len[1];
		int posIdx[2], has = 0;
		Pt posXY[2];
		for (int i = 0; i < 2; i++)
			posIdx[i] = 0, posXY[i] = R[i][0];
			
		for (int it = 0; it < simT; it++) {
			for (int i = 0; i < 2; i++) {
				// move
				if (posXY[i] == R[i][posIdx[i]])
					posIdx[i] = (posIdx[i]+1)%N[i];
				Pt dv = R[i][posIdx[i]] - posXY[i];
				int lenDv = abs(dv.x) + abs(dv.y);
				dv.x /= lenDv, dv.y /= lenDv;
				posXY[i] = posXY[i] + dv;
			}
			if (posXY[0] == posXY[1]) {
				printf("%d %d\n", posXY[0].x, posXY[0].y);
				has = 1;
				break;
			}
		}
		if (!has)
			puts("No Collision");
	}
	return 0;
}
/*
2
4
0  4
2  4
2  5
0  5
4
1  7
1  2
3  2
3  7
4
5  0
6  0
6  1
5  1
4
7  0
8  0
8  1
7  1
*/
