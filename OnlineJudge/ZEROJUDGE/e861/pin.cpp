#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	const static int MAXN = 1000000;
	static int sz[MAXN+5] = {};
	int lastCmd = 0;
	for (int i = 1; i <= MAXN; i++) {
		int cmd;
		while (1) {
			cmd = rand()%4;
			if (cmd == 3 && lastCmd == 3)
				continue;
			if (cmd == 0) {
				int v = rand()*rand()%i;
				sz[i] = sz[v];
				printf("%d %d\n", cmd, v);
				break;
			}
			if (cmd == 1) {
				int x = rand()*rand()%20-10;
				sz[i] = sz[i-1]+1;
				printf("%d %d\n", cmd, x);
				break;
			}
			if (cmd == 2) {
				if (sz[i-1] == 0)
					continue;
				sz[i] = sz[i-1]-1;
				printf("%d\n", cmd);
				break;
			}
			if (cmd == 3) {
				printf("%d\n", cmd);
				break;
			}
		}
		lastCmd = cmd;
	}
	return 0;
}
