#include <cstdio>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
struct node {
    int v, op, l, r;
    map<int, int> R;
};
stringstream sin;
node nd[1000];
int size;
int w[100], l[100];
void build(int idx) {
    string sub;
    sin >> sub;
    if(sub[0] == 'H') {
        nd[idx].l = ++size;
        build(size);
        nd[idx].r = ++size;
        build(size);
        nd[idx].op = 1, nd[idx].v = 'H';
    } else if(sub[0] == 'V') {
        nd[idx].l = ++size;
        build(size);
        nd[idx].r = ++size;
        build(size);
        nd[idx].op = 1, nd[idx].v = 'V';
    } else {
        stringstream nin;
        int x;
        nin << sub;
        nin >> x;
        nd[idx].op = 0, nd[idx].v = x;
    }
}
void dp(int idx) {
    if(nd[idx].op) {
        dp(nd[idx].l);
        dp(nd[idx].r);
        int nl, nw;
        for(map<int, int>::iterator it = nd[nd[idx].l].R.begin();
            it != nd[nd[idx].l].R.end(); it++) {
            for(map<int, int>::iterator jt = nd[nd[idx].r].R.begin();
                jt != nd[nd[idx].r].R.end(); jt++) {
                if(nd[idx].v == 'H') {
                    nl = it->first+jt->first;
                    nw = max(it->second, jt->second);
                    if(nd[idx].R[nl])
                        nd[idx].R[nl] = min(nw, nd[idx].R[nl]);
                    else
                        nd[idx].R[nl] = nw;

                } else {
                    nl = max(it->first, jt->first);
                    nw = it->second+jt->second;
                    if(nd[idx].R[nl])
                        nd[idx].R[nl] = min(nw, nd[idx].R[nl]);
                    else
                        nd[idx].R[nl] = nw;
                }
                //printf("%d %d %d %d\n", nl, nw, nd[nd[idx].l].v, nd[nd[idx].r].v);
            }
        }
        //puts("");
        nd[nd[idx].l].R.clear();
        nd[nd[idx].r].R.clear();
    } else {
        nd[idx].R[l[nd[idx].v]] = w[nd[idx].v];
        nd[idx].R[w[nd[idx].v]] = l[nd[idx].v];
    }
}
int main() {
    string line, stk[1000];
    int stkIdx = 0;
    getline(cin, line);
    stringstream tin;
    tin << line;
    sin.clear();
    while(tin >> line)
        stk[stkIdx++] = line;
    do {
        stkIdx--;
        sin << stk[stkIdx] << ' ';
    } while(stkIdx > 0);
    size = 1;
    build(size);
    int N, L, W;
    while(scanf("%d %d %d", &N, &L, &W) == 3)
        l[N] = L, w[N] = W;
    dp(1);
    int ans = 0xfffffff;
    for(map<int, int>::iterator it = nd[1].R.begin();
        it != nd[1].R.end(); it++) {
        ans = min(ans, it->first * it->second);
    }
    printf("%d\n", ans);
    return 0;
}
