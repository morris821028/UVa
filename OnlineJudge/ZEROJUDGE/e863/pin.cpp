#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	const static int MAXN = 1000000;
	static int sz[MAXN+5] = {};
	int lastCmd = 0;
//	for (int i = 1; i <= MAXN; i++) {
//		printf("%d %d\n", 1, rand()%10);
//	}
//	for (int i = 1; i <= MAXN; i++) {
//		printf("%d %d\n", 1, rand()%10);
//		printf("0 %d\n", MAXN);
//		if (rand()%100 == 0)
//			puts("3");
//	}
//	return 0;
	for (int i = 1; i <= MAXN; i++) {
		int cmd;
		while (1) {
			cmd = rand()%4;
			if (cmd == 3 && lastCmd == 3)
				continue;
			if (cmd == 0) {
				int v;
				if (i > 1000)
					v = i - rand()%100-1;
				else
				 	v = rand()*rand()%i;
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
