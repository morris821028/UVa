#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase, h, l;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &h, &l);
		int car, cx[2505] = {}, cy[2505] = {};
		int hpos[128] = {};
		memset(cx, -1, sizeof(cx));
		memset(cy, -1, sizeof(cy));
		for(int i = 0; i < h; i++) {
			for(int j = 0; j < l; j++) {
				scanf("%d", &car);
				if(car != -1)
					cx[car] = i, cy[car] = j;
			}
		}
		int ret = 0;
		for(int i = 1; cx[i] != -1; i++) {
			ret += cx[i] * 20;
			ret += min(abs(cy[i] - hpos[cx[i]]),
						l - abs(cy[i] - hpos[cx[i]])) * 5;
			hpos[cx[i]] = cy[i];
		}
		printf("%d\n", ret);
	}
	return 0;
}
