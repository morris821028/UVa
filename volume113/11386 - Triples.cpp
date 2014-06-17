#include <stdio.h>
#include <algorithm>
#define N 1048575
using namespace std;
int hash[N+1];
typedef struct {
    int next, t;
    unsigned v;
} Node;
Node nd[5005];
int size = 0;
void insert(unsigned v) {
    static unsigned m;
    static int now, pre;
    m = v&N, now = hash[m], pre = 0;
    while(now) {
        if(nd[now].v == v) {
            nd[now].t ++;
            return ;
        }
        if(nd[now].v > v)
            break;
        pre = now, now = nd[now].next;
    }
    size++;
    if(!pre)    hash[m] = size;
    else        nd[pre].next = size;
    nd[size].v = v, nd[size].t = 1;
    nd[size].next = now;
}
int find(unsigned v) {
    static unsigned m;
    static int now, pre;
    m = v&N, now = hash[m], pre = 0;
    while(now) {
        if(nd[now].v == v)
            return nd[now].t;
        if(nd[now].v > v)
            return 0;
        pre = now, now = nd[now].next;
    }
    return 0;
}
int main() {
    int n, i, j;
    unsigned a[5000], b[5000], f[5000];
    while(scanf("%d", &n) == 1) {
        for(i = 1; i <= size; i++) {
            hash[nd[i].v&N] = 0;
        }
        size = 0;
        for(i = 0; i < n; i++) {
            scanf("%u", &a[i]);
            insert(a[i]);
        }
        sort(a, a+n);
        int m = 0;
        for(i = 0; i < n; i++) {
            if(m == 0 || a[i] != b[m-1]) {
                b[m] = a[i];
                f[m] = 1;
                m++;
            } else {
                f[m-1]++;
            }
        }
        long long ans = 0;
        for(i = 0; i < m; i++) {
            ans += find(b[i]+b[i])*f[i]*(f[i]-1)/2;
            for(j = i+1; j < m; j++) {
                ans += find(b[i]+b[j])*f[i]*f[j];
            }
        }
        printf("%lld\n", ans);

    }
    return 0;
}
