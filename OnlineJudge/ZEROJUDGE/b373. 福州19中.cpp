#include <bits/stdc++.h>
using namespace std;
int BIT[65536], n;
void add(int x, int val) {
	while (x <= n) {
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
	int x;
	while (scanf("%d", &n) == 1) {
		memset(BIT, 0, sizeof(BIT));
		int ret = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			ret += i - query(x);
			add(x, 1); 
		}
		printf("%d", ret);
	}
	return 0;
}
