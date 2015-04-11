// sweep line algorithm
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 0x3f3f3f3f;
const int LCM = 2520; // gcd(1, 2, 3, ..., 10) = 2520, /vx, /vy, vx, vy <= 10
int W, H;
pair<int, int> getTime(int sx, int sy, int vx, int vy) {
	int enter = 0, leave = INF;
	if (vx == 0) {
		if (sx <= 0 || sx >= W)
			leave = 0;
	} else if (vx < 0) {
		enter = max(enter, (sx - W) * LCM / (-vx));
		leave = min(leave, (sx - 0) * LCM / (-vx));
	} else {
		enter = max(enter, (0 - sx) * LCM / (vx));
		leave = min(leave, (W - sx) * LCM / (vx));
	}
	if (vy == 0) {
		if (sy <= 0 || sy >= H)
			leave = 0; 
	} else if (vy < 0) {
		enter = max(enter, (sy - H) * LCM / (-vy));
		leave = min(leave, (sy - 0) * LCM / (-vy));
	} else {
		enter = max(enter, (0 - sy) * LCM / (vy));
		leave = min(leave, (H - sy) * LCM / (vy));
	}
	return make_pair(enter, leave);
}
int main() {
	int testcase, N;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &W, &H);
		scanf("%d", &N);
		
		vector< pair<int, int> > D;
		for (int i = 0; i < N; i++) {
			int sx, sy, vx, vy;
			scanf("%d %d %d %d", &sx, &sy, &vx, &vy);
			pair<int, int> t = getTime(sx, sy, vx, vy);
			if (t.first < t.second) {
				D.push_back(make_pair(t.first, 1));
				D.push_back(make_pair(t.second, -1));
			}
		}
		
		sort(D.begin(), D.end());
		int ret = 0;
		for (int i = 0, s = 0; i < D.size(); i++) {
			s += D[i].second;
			ret = max(ret, s);
		}
		printf("%d\n", ret);
	}
	return 0;
}
