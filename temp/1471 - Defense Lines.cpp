#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;
#define MAXN 262144
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
    while((c = readchar()) < '-') {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int f[MAXN], g[MAXN], A[MAXN], BIT[MAXN];
void modify(int x, int val, int L) {
    while (x <= L) {
        BIT[x] = max(BIT[x], val);
        x += x&(-x);
    }
}
int query(int x) {
    int ret = 0;
    while (x) {
        ret = max(ret, BIT[x]);
        x -= x&(-x);
    }
    return ret;
}
int main() {
    int testcase, N;
//    scanf("%d", &testcase);
    ReadInt(&testcase);
    while (testcase--) {
//        scanf("%d", &N);
        ReadInt(&N);
        map<int, int> R;
        for (int i = 0; i < N; i++) {
//            scanf("%d", &A[i]);
            ReadInt(&A[i]);
            R[A[i]] = 1;
        }
        int size = 0;
        for (map<int, int>::iterator it = R.begin(); it != R.end(); it++)
            it->second = ++size;
        for (int i = 0; i <= size; i++)
            BIT[i] = 0;
        for (int i = 0; i < N; i++)
            A[i] = R[A[i]];
        for (int i = 0; i < N; i++) {
            f[i] = 1;
            if (i > 0 && A[i-1] < A[i])
                f[i] = f[i-1] + 1;
        }
        for (int i = N - 1; i >= 0; i--) {
            g[i] = 1;
            if (i + 1 < N && A[i] < A[i+1])
                g[i] = g[i+1] + 1;
        }
        
        int ret = 0;
        for (int i = 0; i < N; i++) {
            int v = query(A[i] - 1);
            ret = max(ret, v + g[i]);
            modify(A[i], f[i], size);
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
 2
 9
 5 3 4 9 2 8 6 7 1
 7
 1 2 3 10 4 5 6
*/