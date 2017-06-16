#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

const int MAXN = 1<<20;
const int MAXB = MAXN*24;

struct Node {
    int lson, rson;
    int sum;
} node[MAXB];
int nodesize = 0;
int A[MAXN];
int B[MAXN], root[MAXN];
int build(int l, int r) {
    if (l > r)  return 0;
    int k = nodesize++;
    node[k].sum = 0;
    node[k].lson = node[k].rson = -1;
    if (l == r) return k;
    int m = (l + r)/2;
    node[k].lson = build(l, m);
    node[k].rson = build(m+1, r);
    return k;
}

int change(int p, int x, int val, int l, int r) {
    int k = nodesize++;
    node[k] = node[p];
    node[k].sum += val;
    if (l == r) return k;
    int m = (l + r)/2;
    if (x <= m)
        node[k].lson = change(node[p].lson, x, val, l, m);
    else
        node[k].rson = change(node[p].rson, x, val, m+1, r);
    return k;
}

int query(int tp, int tq, int k, int l, int r) {
    if (l == r)
        return l;
    int t = node[node[tp].lson].sum - node[node[tq].lson].sum;
    int m = (l + r)/2;
    if (k <= t)
        return query(node[tp].lson, node[tq].lson, k, l, m);
    else
        return query(node[tp].rson, node[tq].rson, k - t, m+1, r);
}

namespace MM {
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
        void flush() {
        	*p = '\0', p = buf;
            printf("%s", buf);
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
}
int main() {
    int n, q;
//    while (scanf("%d %d", &n, &q) == 2) {
	while (MM::ReadInt(&n)) {
		MM::ReadInt(&q);
        map<int, int> R;
        for (int i = 1; i <= n; i++) {
//            scanf("%d", &A[i]);
			MM::ReadInt(&A[i]);
			B[i] = A[i];
		}
        sort(B+1, B+1+n);
        int size = unique(B+1, B+1+n)-(B+1);
        for (int i = 1; i <= size; i++)
        	R[B[i]] = i;
        
        nodesize = 1;
        root[0] = build(1, size);
        
        for (int i = 1; i <= n; i++) {
            A[i] = R[A[i]];
            root[i] = change(root[i-1], A[i], 1, 1, size);
        }
        
        for (int i = 0; i < q; i++) {
//            scanf("%d %d %d", &x, &y, &k);
			int x, y, k;
			MM::ReadInt(&x);
			MM::ReadInt(&y);
			MM::ReadInt(&k);
            printf("%d\n", B[query(root[y], root[x-1], k, 1, size)]);
        }
    }
    return 0;
}
/*
4  3
1  3  4  3
1  2  2
2  4  1
1  4  4
8  3
4  7  8  5  3  6  1  2
4  5  1
1  8  3
3  5  3
10  10
8  6  2  1  7  3  10  9  5  4
1  8  3
7  7  1
7  8  1
9  9  1
2  10  9
2  7  2
5  7  1
10  10  1
9  10  2
7  10  4
*/

