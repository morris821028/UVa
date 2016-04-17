#include <bits/stdc++.h>
using namespace std;

int main() {
	int st, ed;
	while (scanf("%d %d", &st, &ed) == 2) {
		int used[32767] = {}, u, x;
		queue<int> Q;
		Q.push(st), used[st] = 1;
		while (!Q.empty()) {
			u = Q.front();
			Q.pop();
			if (used[ed])	break;
			x = (u + 1)%10000;
			if (used[x] == 0) {
				used[x] = used[u] + 1;
				Q.push(x);
			}
			x = (u * 2 + 10000)%10000;
			if (used[x] == 0) {
				used[x] = used[u] + 1;
				Q.push(x);
			}
			x = (u / 3);
			if (used[x] == 0) {
				used[x] = used[u] + 1;
				Q.push(x);
			}
		}
		printf("%d\n", used[ed] - 1);
	}
	return 0;
}

