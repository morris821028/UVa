#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
struct BIT16 {
	uint16_t tree[65536+1];
	int n;
	void init(int n) {
		this->n = n;
		memset(tree, 0, sizeof(tree[0])*(n+1));
	}
	int sum(int x) {
		int sum = 0;
		while (x) {
			sum += tree[x];
			x -= x&(-x);
		}
		return sum;
	}
	void inc(int x) {
		if (x == 0) {
			tree[x]++;
			return;
		}
		while (x <= n) {
			tree[x]++;
			x += x&(-x);
		}
	}
} A, B;

void init(int n) {
	A.init(min(n, 65536));
	if (n > 65536)
		B.init(n-65536);
}
int query(int x) {
	int sum = A.sum(min(x, 65536));
	if (x > 65536)
		sum += B.sum(x-65536);
	return sum;
}
void add(int x) {
	if (x <= 65536)
		A.inc(x);
	else
		B.inc(x-65536);
}
int solvable(int n, int m, int g[]) {
	int inv = 0, row, col;
	int tot = n*m;
	init(n*m);
	for (int i = n*m-1; i >= 0; i--) {
		inv += query(g[i])&1;
		if (g[i] == n*m) {
			row = i/m, col = i%m;
		} else {
			add(g[i]);
		}
	}
	return (inv+(n-1-row+m-1-col))%2 == 0;
}

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
int main() {
	int n, m;
	static int g[MAXN];
//	while (scanf("%d %d", &n, &m) == 2) {
	while (ReadInt(&n)) {
		ReadInt(&m);
		for (int i = 0; i < n*m; i++)
			ReadInt(&g[i]);
//			scanf("%d", &g[i]);
		
	    int ret = solvable(n, m, g);
	    puts(ret ? "Y" : "N");
	}
	return 0;
}
/*
4 4
1 2 3 4
5 6 7 8
9 10 11 12
13 15 14 16
2 2
4 3
2 1
2 3
4 1 3
6 2 5
2 3
4 1 3
6 5 2
*/
