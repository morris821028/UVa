#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30000;
struct Rect {
	int lx, ly, rx, ry;
	Rect(int lx=0, int ly=0, int rx=0, int ry=0):
		lx(lx), ly(ly), rx(rx), ry(ry) {}
	int intersect(const Rect &other) const  {
		return max(lx, other.lx) < min(rx, other.rx)
				&& max(ly, other.ly) < min(ry, other.ry);
	}
	int intersect_area(const Rect &other) const {
		int px = max(lx, other.lx), py = max(ly, other.ly);
		int qx = min(rx, other.rx), qy = min(ry, other.ry);
		return (qx - px)*(qy - py);
	}
	void extend(const Rect &other) {
		lx = min(lx, other.lx), ly = min(ly, other.ly);
		rx = max(rx, other.rx),	ry = max(ry, other.ry);
	}
};

int main() {
	int testcase, cases = 0;
	int N[3];
	static Rect A[3][MAXN];
	scanf("%d", &testcase);
	while (testcase--) {
		for (int it = 0; it < 3; it++) {
			scanf("%d", &N[it]);
			for (int i = 0; i < N[it]; i++) {
				int lx, ly, rx, ry;
				scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
				A[it][i] = Rect(lx, ly, rx, ry);
			}
		}
		
		int ret = 0;
		for (int i = 0; i < N[0]; i++) {
			static Rect B[2][MAXN];
			int t1 = 0, t2 = 0;
			for (int j = 0; j < N[1]; j++) {
				if (!A[0][i].intersect(A[1][j]))
					continue;
				B[0][t1++] = A[1][j];
			}
			if (t1 == 0)
				continue;
			for (int j = 0; j < N[1]; j++) {
				if (!A[0][i].intersect(A[2][j]))
					continue;
				B[1][t2++] = A[2][j];
			}	
			if (t2 == 0)		
				continue;
			for (int p = 0; p < t1; p++) {
				for (int q = 0; q < t2; q++) {
					if (!B[0][p].intersect(B[1][q]))
						continue;
					ret++;
				}
			}
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}
/*

## Sample Input ##
```
1
2
5 5 35 25
20 10 50 45
2
10 0 20 30
30 25 45 50
2
15 20 55 35
25 25 60 40
```

## Sample Output ##
```
Case #1: 3
```
*/
