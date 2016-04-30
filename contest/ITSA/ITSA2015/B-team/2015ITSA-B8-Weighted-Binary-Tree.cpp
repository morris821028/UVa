#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, x;
		scanf("%d", &n);
		static int V[262144];
		memset(V, 0, sizeof(V));
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			V[x]++;
		}
		int pos = 0;
		for (int i = 1; i < n; i++) {
			while (V[pos] == 0)	pos++;
			int l = pos;
			V[pos]--;
			while (V[pos] == 0)	pos++;
			int r = pos;
			V[pos]--;
			V[max(l, r)+1]++;
		}
		while (V[pos] == 0)	pos++;
		printf("%d\n", pos);
	}
	return 0;
}
