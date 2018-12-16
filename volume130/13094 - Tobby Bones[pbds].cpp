#include <bits/stdc++.h> 
using namespace std;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int64_t, null_type, less<int64_t>, rb_tree_tag, tree_order_statistics_node_update> set_tree;

const int MAXN = 6000005;
const int INF = 0x3f3f3f3f;
int A[MAXN];
int BLOCK_SIZE;
set_tree B[4096];
void replace(int pos, int val) {
	int bid = pos/BLOCK_SIZE;
	int oldVal = A[pos];
	set_tree &b = B[bid];
	if (oldVal != INF)
		b.erase((int64_t)oldVal<<23|pos);
	b.insert((int64_t)val<<23|pos);
	A[pos] = val;
}
int count(int l, int r, int val) {
	int lb = l/BLOCK_SIZE, rb = r/BLOCK_SIZE;
	int ret = 0;
	if (lb == rb) {
		for (int i = l; i <= r; i++) {
			if (A[i] <= val)
				ret++;
		}
		return ret;
	}
	lb++;
	for (int i = l; i < lb*BLOCK_SIZE; i++) {
		if (A[i] <= val)
			ret++;
	}
	for (int i = rb*BLOCK_SIZE; i <= r; i++) {
		if (A[i] <= val)
			ret++;
	}
	for (int i = lb; i < rb; i++)
		ret += B[i].order_of_key((int64_t)(val+1)<<23);
	return ret;
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
	int n, q;
	int pos, val, l, r, cmd;
	while (scanf("%d %d", &n, &q) == 2) {
//	while (ReadInt(&n)) {
//		ReadInt(&q);
		for (int i = 0; i < n; i++)
			A[i] = INF;
		BLOCK_SIZE = max((int)sqrt(n)*6, 1);
		for (int i = 0; i < n/BLOCK_SIZE+1; i++)
			B[i].clear();
		for (int i = 0; i < q; i++) {
			scanf("%d", &cmd);
//			ReadInt(&cmd);
			if (cmd == 0) {
				scanf("%d %d", &pos, &val);
//				ReadInt(&pos), ReadInt(&val);
				replace(pos, val);
			} else {
				scanf("%d %d %d", &l, &r, &val);
//				ReadInt(&l), ReadInt(&r), ReadInt(&val);
				int ret = count(l, r, val);
				printf("%d\n", ret);
//				bprint.printInt(ret, '\n');
			}
		}
	}
	return 0;
}
/*
5  10
0  0  5
0  1  6
0  2  7
1  0  2  5
1  0  2  6
0  3  5
0  4  6
1  0  4  5
0  0  8
1  0  4  7

*/
