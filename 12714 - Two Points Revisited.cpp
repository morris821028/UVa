#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase, cases = 0;
	int x1, y1, x2, y2;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		printf("Case %d: ", ++cases);
		int vx = y1 - y2, vy = x2 - x1;
		int S = max(max(x1, x2), max(y1, y2));
		if(vx < 0 || (vx == 0 && vy < 0))
			vx = -vx, vy = -vy;
		if(vx >= 0 && vy >= 0)
			printf("0 0 %d %d\n", vx, vy);
		else
			printf("%d %d %d %d\n", 0, S, vx, S + vy);
	}
	return 0;
}
/*
2
4 4 5 5
9 0 10 0
*/
