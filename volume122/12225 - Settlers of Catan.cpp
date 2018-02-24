#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 10005;
int ret[MAXN];
/*
       (0, 2)
             (1, 1)
       (0, 1)      (2, 0)
(-1, 1)      (1, 0)
       (0, 0)      (2,-1)
(-1, 0)      (1,-1)
       (0,-1)
*/
map<pair<int, int>, int> S;
int tot[7] = {};
int place(int x, int y) {
	const int dx[] = {1, 0, -1, -1, 0, 1};
	const int dy[] = {0, 1, 1, 0, -1, -1};
	int mark[6] = {};
	for (int i = 0; i < 6; i++) {
		int tx = x+dx[i], ty = y+dy[i];
		auto it = S.find({tx, ty});
		if (it != S.end())
			mark[it->second] = 1;
	}
	int ch = 0, mn = MAXN+5;
	for (int i = 1; i <= 5; i++) {
		if (mark[i] == 0 && tot[i] < mn) {
			mn = tot[i], ch = i;
		}
	}
	
	S[{x, y}] = ch, tot[ch]++;
//	printf("%d %d, %d\n", x, y, ch);
//	getchar();
	return ch;
}
void build() {
	ret[1] = 1, S[{0, 0}] = 1, tot[1]++;
	int x = 1, y = 0;
	for (int n = 2, e = 1; n < MAXN; e++) {
		for (int i = 0; i < e && n < MAXN; i++)
			ret[n] = place(x, y), x++, n++;
		x--, y++;
		for (int i = 0; i < e-1 && n < MAXN; i++)
			ret[n] = place(x, y), y++, n++;
		x--;
		for (int i = 0; i < e && n < MAXN; i++)
			ret[n] = place(x, y), x--, y++, n++;
		y--;
		for (int i = 0; i < e && n < MAXN; i++)
			ret[n] = place(x, y), x--, n++;
		x++, y--;
		for (int i = 0; i < e && n < MAXN; i++)
			ret[n] = place(x, y), y--, n++;
		x++;
		for (int i = 0; i < e && n < MAXN; i++)
			ret[n] = place(x, y), x++, y--, n++;
		y++;
	}
}
int main() {
	build();
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		printf("%d\n", ret[n]);
	}
	return 0;
}
