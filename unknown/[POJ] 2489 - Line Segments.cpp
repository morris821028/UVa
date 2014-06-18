#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
struct Pt {
    int x, y;
    bool operator<(const Pt &a) const {
        if(a.x != x)
            return x < a.x;
        return y < a.y;
    }
    bool operator>(const Pt &a) const {
        if(a.x != x)
            return x > a.x;
        return y > a.y;
    }
};
struct cmp {
    bool operator() (const Pt &a, const Pt &b) const {
        return a > b;
    }
};
struct Seg {
    int a, b;
    int c; // ax + by = c maybe use long long
    Pt s, e;
    bool operator<(const Seg &A) const {
        if(A.a != a)    return a < A.a;
        if(A.b != b)    return b < A.b;
        if(A.c != c)    return c < A.c;
        if(s < A.s)     return true;
        else            return false;
    }
};
int gcd(int x, int y) {
    if(x == 0)  return y;
    if(y == 0)  return x;
    if(x < 0)   x = -x;
    if(y < 0)   y = -y;
    long long t;
    while(x%y)
        t = x, x = y, y = t%y;
    return y;
}
Seg D[100000];
int main() {
    int testcase, cases = 0;
    int n;
    int i, j, k;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        int g;
        for(i = 0; i < n; i++) {
            scanf("%d %d", &D[i].s.x, &D[i].s.y);
            scanf("%d %d", &D[i].e.x, &D[i].e.y);
            if(D[i].e < D[i].s)
                swap(D[i].e, D[i].s);
            D[i].a = D[i].s.y-D[i].e.y;
            D[i].b = -D[i].s.x+D[i].e.x;
            g = gcd(D[i].a, D[i].b);
            if(g == 0) {D[i].a = D[i].b = 0;}
            else    D[i].a /= g, D[i].b /= g;
            if(D[i].a < 0)  D[i].a *= -1, D[i].b *= -1;
            D[i].c = D[i].a*D[i].s.x + D[i].b*D[i].s.y;
        }
        sort(D, D+n);
        priority_queue<Pt, vector<Pt>, cmp> pQ;
        long long ret = 0;
        for(i = 0; i < n; ) {
            j = i;
            while(i < n && D[i].a == D[j].a && D[i].b == D[j].b && D[i].c == D[j].c)
                i++;
            while(!pQ.empty()) //<pQ.clear()>
                pQ.pop();
            for(k = j; k < i; k++) {
                while(!pQ.empty()) {
                    if(D[k].s.x == D[k].e.x) {
                        if(pQ.top().y <= D[k].s.y)
                            pQ.pop();
                        else    break;
                    } else {
                        if(pQ.top().x <= D[k].s.x)
                            pQ.pop();
                        else    break;
                    }
                }
                ret += pQ.size();
                pQ.push(D[k].e);
            }
        }
        printf("Scenario #%d:\n%I64d\n", ++cases, ret);
        if(testcase)
            puts("");
    }
    return 0;
}
