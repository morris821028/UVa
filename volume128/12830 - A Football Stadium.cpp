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
        int h, w;
        int x, y;
        scanf("%d %d", &h, &w);
        int op, i, j;
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        	scanf("%d %d", &tree[i].x, &tree[i].y);
        tree[n++] = Pt(0, 0);
        tree[n++] = Pt(h, w);
        tree[n++] = Pt(h, 0);
        tree[n++] = Pt(0, w);
		sort(tree, tree+n);
        int area = 0;
        for(i = 0; i < n; i++) {
            int mny = 0, mxy = w;
            for(j = i+1; j < n; j++) {
                area = max(area, (tree[j].x-tree[i].x)*(mxy-mny));
                if(tree[j].x == tree[i].x)
                    continue;
                if(tree[j].y > tree[i].y)
                    mxy = min(mxy, tree[j].y);
                else
                    mny = max(mny, tree[j].y);
            }
        }
        sort(tree, tree+n, cmp);
        for(i = 0; i < n; i++) {
            int mnx = 0, mxx = h;
            for(j = i+1; j < n; j++) {
                area = max(area, (tree[j].y-tree[i].y)*(mxx-mnx));
                if(tree[j].y == tree[i].y)
                    continue;
                if(tree[j].x > tree[i].x)
                    mxx = min(mxx, tree[j].x);
                else
                    mnx = max(mnx, tree[j].x);
            }
        }
        printf("Case %d: %d\n", ++cases, area);
    }
    return 0;
}
