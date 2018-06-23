#include <bits/stdc++.h> 
using namespace std;

const int MAXL = 1000005;
int cost[MAXL], pass[MAXL];

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
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

void process(int a[], int n, int L) {
	static int zpos[MAXL], move[MAXL] = {};
	int zidx = 0, pos = 0;

	memset(move, -1, sizeof(move[0])*L);

	for (int i = 0; i < n; i++) {
		if (a[i] == 0) {
			pass[pos]++;
			zpos[zidx] = i;
			pos++, zidx++;
		} else {
			pos += a[i];
			int left = min(zidx, a[i]);
			for (int j = left; j >= 1; j--) {
				int c = i - zpos[zidx-j] - j + 1;
				move[pos-j] = c;
				pass[pos-j]++;
				cost[pos-j] += c;
			}
		}
	}

	zidx = 0, pos--;
	for (int i = n-1; i >= 0; i--) {
		if (a[i] == 0) {
			zpos[zidx] = i;
			pos--, zidx++;
		} else {
			pos -= a[i];
			int right = min(zidx, a[i]);
			for (int j = 1; j <= right; j++) {
				int c = zpos[zidx-j] - i - j + 1;
				if (move[pos+j] == -1) {
					pass[pos+j]++;
					cost[pos+j] += c;
				} else {
					cost[pos+j] += min(0, c-move[pos+j]);
				}
			}
		}
	}
}

int main() {
	int testcase;
	int R, L;
	static int a[MAXL];
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d %d", &R, &L);
		ReadInt(&R), ReadInt(&L);

		memset(cost, 0, sizeof(cost[0])*L);
		memset(pass, 0, sizeof(pass[0])*L);

		for (int i = 0; i < R; i++) {
			int n;
//			scanf("%d", &n);
			ReadInt(&n);
			for (int j = 0; j < n; j++)
//				scanf("%d", &a[j]);
				ReadInt(&a[j]);
			process(a, n, L);
		}

		int mn = L+1;
		for (int i = 0; i < L; i++) {
			if (pass[i] == R && cost[i] < mn)
				mn = cost[i];
		}

//		printf("%d\n", mn);
		bprint.printInt(mn, '\n');
		for (int i = 0, f = 0; i < L; i++) {
			if (pass[i] == R && cost[i] == mn) {
//				printf("%d", i);
//				putchar(' ');
				bprint.printInt(i, ' ');
			}
		}
//		puts("");
		bprint.printChar('\n');
	}
	return 0;
}
/*
1
4 10
8 1 2 1 0 1 2 0 1
7 2 2 2 1 0 1 0
6 1 3 2 0 2 1
7 2 1 2 0 2 1 0
*/
