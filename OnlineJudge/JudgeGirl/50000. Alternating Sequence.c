#include <stdio.h> 
#include <stdlib.h>
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
int now_c, now_f, seg, ret;
int N, K;
void update(int x) {
	if (x > 0) {
		if (now_f == 1) {
			now_c++;
		} else if (now_f == -1) {
			// ----/++++
			//	  ^
			if (now_c > K) {
				seg = 0, now_c = 1, now_f = 1;
			} else if (now_c < K) {
				seg = 0, now_c = 1, now_f = 1;
			} else {
				seg++, now_c = 1, now_f = 1;
			}
		} else {
			// 0000/++++
			//	  ^
			seg = 0, now_c = 1, now_f = 1;
		}
	} else if (x < 0) {
		if (now_f == -1) {
			now_c++;
		} else if (now_f == 1) {
			// ++++/----
			//	  ^
			if (now_c > K) {
				if (seg+1 >= 3)	ret = max(ret, seg+1);
				seg = 1, now_c = 1, now_f = -1;
			} else if (now_c < K) {
				seg = -0x3f3f3f3f, now_c = 1, now_f = -1;
			} else {
				if (seg < 0)	seg = 0;
				if (seg+1 >= 3)	ret = max(ret, seg+1);
				seg++, now_c = 1, now_f = -1;
			}
		} else {
			// 0000/----
			//	  ^
			seg = -0x3f3f3f3f, now_c = 1, now_f = -1;
		}
	} else {
		if (now_f == 0) {
			now_c++;
		} else if (now_f == 1) {
			// ++++/0000
			//    ^
			if (now_c >= K) {
				if (seg+1 >= 3)	ret = max(ret, seg+1);
				seg = -0x3f3f3f3f, now_c = 1, now_f = 0;
			} else {
				seg = -0x3f3f3f3f, now_c = 1, now_f = 0;
			}
			seg = -0x3f3f3f3f, now_c = 1, now_f = 0;
		} else {
			// ----/0000
			//    ^
			seg = -0x3f3f3f3f, now_c = 1, now_f = 0;
		}
	}
}
int main() {
	int x;
	while (scanf("%d", &K) == 1) {
		now_c = 0, now_f = 0, seg = 0, ret = 0;
		while (scanf("%d", &x) == 1 && x)
			update(x);
		update(0);
		printf("%d\n", ret*K);
	}
	return 0;
}
/*
2
-3 4 6 -5 -3 10 7 -1 -1 3 -7 3 0
3
-1 -1 1 1 1 -1 -1 -1 0
3
1 1 1 -1 -1 -1 1 1 1 1 -1 -1 -1 1 1 1 -1 -1 -1 1 1 1 0
*/


