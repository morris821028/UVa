#include <stdio.h>
#include <assert.h>
#define MAXN 16
#define MAXS 32
#define MAXMEM (896*1024/4)

static int h[MAXMEM];
static inline void online_printInt(int x) {
	static char ch[16];
	static int idx;
	idx = 0;
	if (x == 0)	ch[++idx] = 0;
	while (x > 0) ch[++idx] = x % 10, x /= 10;
	while (idx) 
		putchar(ch[idx--]+48);
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		FILE *fin[MAXN];
		for (int i = 0; i < n; i++) {
			char s[MAXS];
			assert(scanf("%s", s) == 1);
			fin[i] = fopen(s, "rb");
			assert(fin[i] != NULL && "Fail: Open File");
		}

		int size = MAXMEM / n;
		int stat[MAXN], off[MAXN], idx[MAXN];
		int has = n;
		for (int i = 0, s = 0; i < n; i++) {
			off[i] = s, s += size, idx[i] = 0;
			stat[i] = fread(h+off[i], sizeof(int), size, fin[i]);
			if (stat[i] == 0)
				fclose(fin[i]);
			has -= stat[i] == 0;
		}

		while (has) {
			int mnIdx = -1, mnVal;
			for (int i = 0; i < n; i++) {
				if (idx[i] < stat[i] && (mnIdx == -1 || h[off[i]+idx[i]] < mnVal))
					mnVal = h[off[i]+idx[i]], mnIdx = i;
			}
//			printf("%d\n", mnVal);
			online_printInt(mnVal), putchar('\n');
			idx[mnIdx]++;

			if (stat[mnIdx] == idx[mnIdx]) {
				stat[mnIdx] = fread(h+off[mnIdx], sizeof(int), size, fin[mnIdx]);
				idx[mnIdx] = 0;
				if (stat[mnIdx] == 0)
					fclose(fin[mnIdx]);
				has -= stat[mnIdx] == 0;
			}
		}
	}
	return 0;
}

