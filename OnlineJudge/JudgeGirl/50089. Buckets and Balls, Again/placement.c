#include "placement.h"
#include <limits.h>

#define HARG int bin[], int n, int ball[], int m, int type, int ret[]
#define ARG bin, n, ball, m, type, ret
#define MAXN 1024
static void ffit(HARG) {
	int use[MAXN] = {};
	for (int i = 0; i < m; i++) {
		int x = ball[i];
		ret[i] = -1;
		for (int j = 0; j < n; j++) {
			if (use[j]+x <= bin[j]) {
				ret[i] = j;
				use[j] += x;
				break;
			}
		}
	}
}
static void bfit(HARG) {
	int use[MAXN] = {};
	for (int i = 0; i < m; i++) {
		int x = ball[i];
		int mn = INT_MAX, mnt = -1;
		for (int j = 0; j < n; j++) {
			if (use[j]+x <= bin[j] && bin[j]-use[j] < mn)
				mn = bin[j]-use[j], mnt = j;
		}
		ret[i] = mnt;
		if (mnt != -1)
			use[mnt] += x;
	}
}
static void wfit(HARG) {
	int use[MAXN] = {};
	for (int i = 0; i < m; i++) {
		int x = ball[i];
		int mx = INT_MIN, mxt = -1;
		for (int j = 0; j < n; j++) {
			if (use[j]+x <= bin[j] && bin[j]-use[j] >= mx)
				mx = bin[j]-use[j], mxt = j;
		}
		ret[i] = mxt;
		if (mxt != -1)
			use[mxt] += x;
	}
}
void place(HARG) {
	static void (*func[])() = {ffit, bfit, wfit};
	(*func[type])(ARG);	
}
