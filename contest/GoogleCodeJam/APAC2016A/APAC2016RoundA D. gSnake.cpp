#include <bits/stdc++.h> 
using namespace std;
const int MAXS = 100005;
const int MAXT = 10e9;
const int dx[4] = {0, 1, 0, -1};	// right, down, left, up
const int dy[4] = {1, 0, -1, 0};
int X[MAXS];
char CMD[MAXS][4];
int main() {
	int testcase, cases = 0, R, C, S;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &S, &R, &C);
		for (int i = 0; i < S; i++)
			scanf("%d %s", &X[i], &CMD[i]);
			
		int len = 1, x = 1, y = 1, dir = 0;
		int cmdIdx = 0, cnt = 0;
		
		set< pair<int, int> > F;
		map< pair<int, int>, int > PASS;
		
		for (int i = 1; i <= MAXT; i++) {
			if (cmdIdx == S && cnt > max(R, C)*2)	// cycle
				break;
			x += dx[dir], y += dy[dir];
			if (x == 0)	x = R;
			if (x > R)	x = 1;
			if (y == 0)	y = C;
			if (y > C)	y = 1;
			
			int &step = PASS[{x, y}]; 
			if (step == 0)	step = -0x3f3f3f3f;
			if (i - step < len)
				break;
			step = i;			
			
			if ((x+y)%2 == 1 && !F.count({x, y})) {
				F.insert({x, y});
				len++, cnt = 0;
			}
			
			if (cmdIdx < S && i == X[cmdIdx]) {
				if (CMD[cmdIdx][0] == 'R')
					dir = (dir+1)%4;
				else
					dir = (dir+3)%4;
				cmdIdx++, cnt = 0;
			}
			cnt++;
		}
		printf("Case #%d: %d\n", ++cases, len);
	}
	return 0;
}
