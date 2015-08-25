#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 262144;
int parent[MAXN], eat[MAXN];
int findp(int x) {
	return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
void joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x != y)
		parent[x] = y;
}
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n*3; i++)
		parent[i] = i;
	// x => x1: same, x2: eat, x3: be eaten
	for (int i = 1; i <= n; i++)
		eat[i] = i+n, eat[i+n] = i+n*2, eat[i+n*2] = i;
	int ret = 0, cmd, x, y;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &cmd, &x, &y);
		if (x > n || y > n) {
			ret ++;
			continue;
		}
		int a[3], b[3];
		a[0] = findp(x), a[1] = eat[a[0]], a[2] = eat[a[1]];
		b[0] = findp(y), b[1] = eat[b[0]], b[2] = eat[b[1]];
		int flag = a[0] == b[0] || a[0] == b[1] || a[0] == b[2];
		if (cmd == 1) {
			if (flag) {
				if (a[0] != b[0])
					ret++;
			} else {
				for (int i = 0; i < 3; i++)
					parent[b[i]] = a[i];
			}
		} else {
			if (x == y) {
				ret++;
			} else if (flag) {
				if (a[0] != b[1])
					ret++;
			} else {
				for (int i = 0; i < 3; i++)
					parent[b[i]] = a[(i+2)%3];
			}
		}
	}
	printf("%d\n", ret);
	return 0;
}
