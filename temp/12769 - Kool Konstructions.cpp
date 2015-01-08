#include <stdio.h> 
#include <string.h> 
#define MAXN 100000
int BIT[MAXN + 5];
void modify(int x, int val, int L) {
	while (x <= L) {
		BIT[x] += val;
		x += x&(-x);
	}
}
int query(int x) {
	int ret = 0;
	while (x) {
		ret += BIT[x];
		x -= x&(-x);
	}
	return ret;
}
int main() {
	int n, a, b, y;
	char cmd[8];
	while (scanf("%d", &n) == 1 && n) {
		memset(BIT, 0, sizeof(BIT));
		for (int i = 0; i < n; i++) {
			scanf("%s", cmd);
			if (cmd[0] == 'B') {
				scanf("%d %d %d", &a, &b, &y);
				modify(a, y, MAXN);
				modify(b + 1, -y, MAXN);
			} else {
				scanf("%d", &a);
				int ret = query(a);
				printf("%d\n", ret);
			}
		}
	}
	return 0;
}
/*
9
B 5 5 2
B 8 8 2
B 10 13 1
Q 8
B 8 13 1
Q 8
B 15 16 1
B 2 10 1
Q 8
9
B 5 5 2
B 8 8 2
B 10 13 1
Q 8
B 8 13 1
Q 8
B 15 16 1
B 2 10 1
Q 8
0
*/
