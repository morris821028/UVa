#include <stdio.h>
#include <limits.h>
#include <assert.h>
#define MAXN 16
#define MAXS 32
#define MAXMEM (896*1024/4)

static int _mem[MAXMEM];
static int *h[MAXN];
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
		static FILE *fin[MAXN];
		for (int i = 0; i < n; i++) {
			char s[MAXS];
			assert(scanf("%s", s) == 1);
			fin[i] = fopen(s, "rb");
			assert(fin[i] != NULL && "Fail: Open File");
		}

		int size = MAXMEM / n;
		static int stat[MAXN][2];
		int has = n;
		for (int i = 0; i < n; i++)
			h[i] = _mem + size*i;
		for (int i = 0; i < n; i++) {
			stat[i][0] = 0;
			stat[i][1] = fread(h[i], sizeof(int), size, fin[i]);
			has -= stat[i][1] == 0;
		}
		do {
			int mnIdx = -1, mnVal = INT_MAX;
			{
#define CMD {\
	if (stat[i][1] && h[i][stat[i][0]] < mnVal)\
	mnVal = h[i][stat[i][0]], mnIdx = i; \
	i++;}

				int ln = (n+3)>>2, i = 0;
				switch(n&3) {
					case 0: do { CMD;
					case 3: CMD;			
					case 2: CMD;			
					case 1: CMD;			
					} while (--ln > 0);
				}
			}
			
			stat[mnIdx][0]++;
			online_printInt(mnVal), putchar('\n');

			if (stat[mnIdx][0] == stat[mnIdx][1]) {
				stat[mnIdx][0] = 0;
				stat[mnIdx][1] = fread(h[mnIdx], sizeof(int), size, fin[mnIdx]);
				has -= stat[mnIdx][1] == 0;
			}
		} while (has);
	}
	return 0;
}


