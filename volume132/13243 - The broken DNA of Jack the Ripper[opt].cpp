#include <bits/stdc++.h>
using namespace std;

inline int toIndex(char c) {
	switch(c) {
		case 'A': return 0;
		case 'C': return 1;
		case 'G': return 2;
		case 'T': return 3;
		case '-': return 4;
	}
	assert(false);
}

const int MAXN = 20005;
const int MAXS = 105;
uint64_t bit[MAXN][4][2];
uint64_t mask[MAXN][2];

void store(char s[], int i, int m) {
	for (int j = 0; j < m; j++) {
		int c = toIndex(s[j]);
		if (c == 4) {
			mask[i][j>>6] |= 1LLU<<(j&63);
		} else {
			bit[i][c][j>>6] |= 1LLU<<(j&63);
		}
	}
}
class Print {
public:
    static const int N = 1048576;
    char buf[N], *p, *end;
    Print() {
        p = buf, end = buf + N - 1;
    }
    void printInt(int x, char padding) {
        static char stk[16];
        int idx = 0;
        stk[idx++] = padding;
        if (!x)	
            stk[idx++] = '0';
        while (x)
            stk[idx++] = x%10 + '0', x /= 10;
        while (idx) {
            if (p == end) {
                *p = '\0';
                printf("%s", buf), p = buf;
            }
            *p = stk[--idx], p++;
        }
    }
    void printChar(char padding) {
    	if (p == end) {
    		*p = '\0';
            printf("%s", buf), p = buf; 
		}
		*p = padding, p++;
	}
    static inline void online_printInt(int x) {
        static char ch[16];
        static int idx;
        idx = 0;
        if (x == 0)	ch[++idx] = 0;
        while (x > 0) ch[++idx] = x % 10, x /= 10;
        while (idx) 
            putchar(ch[idx--]+48);
    }
    ~Print() {
        *p = '\0';
        printf("%s", buf);
    }
} bprint;
int main() {
	int n;
	char s[105];
	while (scanf("%d", &n) == 1) {
		memset(bit, 0, sizeof(bit));
		memset(mask, 0, sizeof(mask));
		while (getchar() != '\n');
		fgets(s, MAXS, stdin);
		int m = strlen(s)-1;
		int b = (m>>6) + ((m&63) != 0);
		store(s, 0, m);
		static int ret[MAXN];
		for (int i = 1; i < n; i++) {
			fgets(s, MAXS, stdin);
			store(s, i, m);
			int rcnt = 0;
			for (int j = 0; j < i; j++) {
				int ok = 1;
				for (int c = 0; c < 4; c++) {
					for (int k = 0; k < b; k++) {
						uint64_t diff = bit[i][c][k]^bit[j][c][k];
						if (diff && (diff&(mask[i][k]|mask[j][k])) != diff) {
							ok = 0;
							goto DONE;
						}
					}
				}
				DONE:
				if (ok)
					ret[rcnt++] = j;
			}
			if (rcnt) {
				bprint.printInt(i+1, ':');
				bprint.printChar(' ');
//				printf("%d:", i+1);
				for (int j = 0; j < rcnt; j++) {
					bprint.printInt(ret[j]+1, j == rcnt-1 ? '\n' : ' ');
//					printf(" %d", ret[j]+1);
				}
//				puts("");
			}
		}
	}
	return 0;
}
/*
8
AC-CG-
A-A-GG
ACACGT
ACACGG
ACACAC
---TT-
------
ACACAC
*/
