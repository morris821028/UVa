#include <stdio.h>
#include <algorithm>
using namespace std;
// same 10043 - Chainsaw Massacre.
struct Pt {
    int x, y;
    Pt(int a = 0, int b = 0):
    x(a), y(b){}
    bool operator<(const Pt &p) const {
        if(p.x != x)
            return x < p.x;
        return y < p.y;
    }
};
bool cmp(Pt a, Pt b) {
    if(a.y != b.y)
        return a.y < b.y;
    return a.x < b.x;
}
Pt tree[3000];
int main() {
    int testcase, cases = 0;
    scanf("%d", &testcase);
    while(testcase--) {
        int h, w, n;
        scanf("%d %d %d", &n, &h, &w);
        for (int i = 0; i < n; i++)
            scanf("%d %d", &tree[i].x, &tree[i].y);
        tree[n++] = Pt(0, 0);
        tree[n++] = Pt(h, w);
        tree[n++] = Pt(h, 0);
        tree[n++] = Pt(0, w);
        sort(tree, tree+n);
        int P = 0, Q = 0, L = 0;
        for (int i = 0; i < n; i++) {
            int mny = 0, mxy = w;
            for (int j = i+1; j < n; j++) {
                int l = min(tree[j].x-tree[i].x, mxy-mny);
                if (l > L)
                    P = tree[i].x, Q = mny, L = l;
                if(tree[j].x == tree[i].x)
                    continue;
                if(tree[j].y > tree[i].y)
                    mxy = min(mxy, tree[j].y);
                else
                    mny = max(mny, tree[j].y);
            }
        }
        sort(tree, tree+n, cmp);
        for (int i = 0; i < n; i++) {
            int mnx = 0, mxx = h;
            for (int j = i+1; j < n; j++) {
                int l = min(tree[j].y-tree[i].y, mxx-mnx);
                if (l > L)
                    P = mnx, Q = tree[i].y, L = l;
                if(tree[j].y == tree[i].y)
                    continue;
                if(tree[j].x > tree[i].x)
                    mxx = min(mxx, tree[j].x);
                else
                    mnx = max(mnx, tree[j].x);
            }
        }
        if (cases++)    puts("");
        printf("%d %d %d\n", P, Q, L);
    }
    return 0;
}