#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;
struct Node {
    int l, r, cnt;
    long long sum[5];
};
Node ST[262145];
int Clear(int k, int l, int r) {
    ST[k].l = l;
    ST[k].r = r;
    ST[k].cnt = 0;
    memset(ST[k].sum, 0, sizeof(ST[k].sum));
    if(l < r) {
        int m = (l+r)/2;
        Clear(k<<1, l, m);
        Clear(k<<1|1, m+1, r);
    }
}
void ins(int k, int qx, int qidx) {
    int m = (ST[k].l+ST[k].r)/2;
    if(ST[k].l == ST[k].r) {
        ST[k].sum[1] = qx;
        ST[k].cnt = 1;
        return;
    }
    if(qidx <= m) {
        ins(k<<1, qx, qidx);
    } else {
        ins(k<<1|1, qx, qidx);
    }
    for(int i = 0; i < 5; i++)
        ST[k].sum[i] = ST[k<<1].sum[i];
    for(int i = 0; i < 5; i++)
        ST[k].sum[(ST[k<<1].cnt+i)%5] += ST[k<<1|1].sum[i];
    ST[k].cnt = ST[k<<1].cnt + ST[k<<1|1].cnt;
}
void del(int k, int qx, int qidx) {
    int m = (ST[k].l+ST[k].r)/2;
    if(ST[k].l == ST[k].r) {
        ST[k].sum[1] = 0;
        ST[k].cnt = 0;
        return;
    }
    if(qidx <= m) {
        del(k<<1, qx, qidx);
    } else {
        del(k<<1|1, qx, qidx);
    }
    for(int i = 0; i < 5; i++)
        ST[k].sum[i] = ST[k<<1].sum[i];
    for(int i = 0; i < 5; i++)
        ST[k].sum[(ST[k<<1].cnt+i)%5] += ST[k<<1|1].sum[i];
    ST[k].cnt = ST[k<<1].cnt + ST[k<<1|1].cnt;
}
char cmd[100000][50];
int x[100000];
int main() {
    int n, m;
    while(scanf("%d", &n) == 1) {
        int i;
        map<int, int> r;
        for(i = 0; i < n; i++) {
            scanf("%s", cmd[i]);
            if(cmd[i][0] == 'a') {
                scanf("%d", &x[i]);
                r[x[i]] = 1;
            } else if(cmd[i][0] == 'd') {
                scanf("%d", &x[i]);
                r[x[i]] = 1;
            }
        }
        i = 0;
        for(map<int, int>::iterator it = r.begin();
            it != r.end(); it++) {
            it->second = i;
            i++;
        }
        m = i;
        Clear(1, 0, m);
        for(i = 0; i < n; i++) {
            if(cmd[i][0] == 'a') {
                ins(1, x[i], r[x[i]]);
            } else if(cmd[i][0] == 'd') {
                del(1, x[i], r[x[i]]);
            } else
                printf("%lld\n", ST[1].sum[3]);
        }
    }
    return 0;
}
