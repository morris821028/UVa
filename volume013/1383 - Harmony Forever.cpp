#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 524288
struct E {
	int value, index;
	E(int a = 0, int b = 0):
		value(a), index(b) {}
	bool operator<(const E &a) const {
		return value < a.value;
	}
};
E tree[(MAXN<<1) + 10];
int M;
void setTree(int s, int t) {
    int i;
    for(i = 2 * M - 1; i >= 0; i--) {
    	tree[i] = E(0x3f3f3f3f, 0);
    }
}
E query(int s, int t) {
    E ret(0x3f3f3f3f, 0);
    for(s = s + M - 1, t = t + M + 1; (s^t) != 1;) {
        if(~s&1)
            ret = min(ret, tree[s^1]);
        if(t&1)
            ret = min(ret, tree[t^1]);
        s >>= 1, t >>= 1;
    }
    return ret;
}
void update(int s, E v) {
	tree[s + M] = v;
	for (s = s + M; s > 0; s >>= 1)
		tree[s] = min(tree[s], v);
}
int main() {
	int n, x, cases = 0;
	char cmd[5];
	while (scanf("%d", &n) == 1 && n) {
		for (M = 1; M < 500000+2; M <<= 1);
		setTree(0, M);
		int B = 0;
		vector<int> BX;
		if (cases++)
			puts("");
		printf("Case %d:\n", cases);
		for (int i = 0; i < n; i++) {
			scanf("%s %d", cmd, &x);
			if (cmd[0] == 'B') {
				update(x + 1, E(x + 1, ++B));
				BX.push_back(x);
			} else {
				if (BX.size() == 0)
					puts("-1");
				else if (x < 5000) {
					int mn1 = 0x3f3f3f3f, mn2 = -1, u;
					for (int i = BX.size() - 1; i >= 0; i--) {
						u = BX[i]%x;
						if (u == 0) {
							mn1 = 0, mn2 = i + 1;
							break;
						}
						if (u < mn1)
							mn1 = u, mn2 = i + 1;
					}
					printf("%d\n", mn2);
				} else {
					int mn1 = 0x3f3f3f3f, mn2 = -1;
					for (int y = 0; y <= 500000; y += x) {
						E t = query(y + 1, min(y + 1 + x - 1, 500000));
						if (t.value - y < mn1 || (t.value - y == mn1 && t.index > mn2))
							mn1 = t.value - y, mn2 = t.index;
					}
					printf("%d\n", mn2);
				}
			}
		}
	}
	return 0;
}
