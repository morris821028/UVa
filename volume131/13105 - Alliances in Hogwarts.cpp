#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20002;

class DisjointSet {
public:
	short parent[MAXN], weight[MAXN];
	int findp(int x) {
		if (parent[x] == -1)
			return -1;
	    return parent[x] == x ? x : parent[x] = findp(parent[x]);
	}
	int joint(int tx, int ty) {
	    int x = findp(tx), y = findp(ty);
	    if (x == y && x != -1)	return 0;
	    if (x == -1)	x = tx, parent[tx] = tx;
	    if (y == -1)	y = ty, parent[ty] = ty;
	    if (weight[x] > weight[y])
	        weight[x] += weight[y], parent[y] = x;
	    else
	        weight[y] += weight[x], parent[x] = y;
	    return 1;
	}
	void init(int n) {
		for (int i = 0; i <= n; i++)
			parent[i] = -1, weight[i] = 1;
	}
} D;
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
int mkFriend(int x, int y) {
	D.joint(x*2, y*2);
	D.joint(x*2+1, y*2+1);
;}
int mkEmeny(int x, int y) {
	D.joint(x*2, y*2+1);
	D.joint(x*2+1, y*2);
}
int isFriend(int x, int y) {
	int xp, xn, yp, yn;
	xp = D.findp(x*2);
	xn = D.findp(x*2+1);
	yp = D.findp(y*2);
	yn = D.findp(y*2+1);
	if (x == y)
		return 1;
	if (xp == -1 || yp == -1)
		return -1;
	if (xp == yp)
		return 1;
	return 0;
}
int isEmeny(int x, int y) {
	int xp, xn, yp, yn;
	xp = D.findp(x*2);
	xn = D.findp(x*2+1);
	yp = D.findp(y*2);
	yn = D.findp(y*2+1);
	if (xp == -1 || yp == -1)
		return -1;
	if (xp == yn)
		return 1;
	return 0;
}
int main() {
	int n, m;
	static char buffer[16777216];
	static char *bptr = buffer;
//	while (scanf("%d %d", &n, &m) == 2) {
	while (ReadInt(&n)) {
		ReadInt(&m);
		D.init(2*n);
		int cmd, x, y;
		for (int i = 0; i < m; i++) {
//			scanf("%d %d %d", &cmd, &x, &y);
			ReadInt(&cmd), ReadInt(&x), ReadInt(&y);
			if (cmd == 1) {
				if (isEmeny(x, y) == 1)	// emeny
					(*bptr) = '-', bptr++, (*bptr) = '1', bptr++, (*bptr) = '\n', bptr++;
				else
					mkFriend(x, y);
			} else if (cmd == 2) {
				if (isFriend(x, y) == 1) // friend
					(*bptr) = '-', bptr++, (*bptr) = '1', bptr++, (*bptr) = '\n', bptr++;
				else
					mkEmeny(x, y);
			} else if (cmd == 3) {
				int t = isFriend(x, y) > 0;
				(*bptr) = '0' + t, bptr++, (*bptr) = '\n', bptr++;
			} else {
				int t = isEmeny(x, y) > 0;
				(*bptr) = '0' + t, bptr++, (*bptr) = '\n', bptr++;
			}
		}
	}
	*bptr = '\0';
	fputs(buffer, stdout);
	return 0;
}

