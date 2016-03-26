#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <math.h>
using namespace std;

struct Pt {
    int x, y, v;
    Pt(int a = 0, int b = 0):
    x(a), y(b) {}
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
    bool operator<(const Pt &a) const {
        if (x != a.x)
            return x < a.x;
        if (y != a.y)
            return y < a.y;
        return false;
    }
};
struct Seg {
    int xl, xr, y;
    Seg(int a = 0, int b = 0, int c = 0):
    xl(a), xr(b), y(c) {}
    bool operator<(const Seg &u) const {
        return xl < u.xl;
    }
};
Pt P[131072], D[131072];
int BIT[262144];
void modify(int x, int val, int L) {
    while (x <= L)
        BIT[x] += val, x += x&(-x);
}
int query(int x) {
    int sum = 0;
    while (x)
        sum += BIT[x], x -= x&(-x);
    return sum;
}
void solve(int N, int M) {
    map<int, int> RX, RY;
    for (int i = 0; i < N; i++)
        RX[P[i].x] = RY[P[i].y] = 0;
    for (int i = 0; i < M; i++)
        RX[D[i].x] = RY[D[i].y] = 0;
    
    int label_x = 0, label_y = 0;
    
    for (auto &x : RX)
        x.second = ++label_x;
    for (auto &y : RY)
        y.second = ++label_y;
    
    memset(BIT, 0, sizeof(BIT));
    
    for (int i = 0; i < N; i++)
        P[i].x = RX[P[i].x], P[i].y = RY[P[i].y];
    for (int i = 0; i < M; i++)
        D[i].x = RX[D[i].x], D[i].y = RY[D[i].y];
    
    vector<Seg> segs;
    for (int i = 0; i < M; i++) {
        if (D[i].y == D[(i+1)%M].y) {
            int xl = min(D[i].x, D[(i+1)%M].x);
            int xr = max(D[i].x, D[(i+1)%M].x);
            segs.push_back(Seg(xl, xr, D[i].y));
        }
    }
    
    long long outer_val = 0;
    sort(P, P+N);
    sort(segs.begin(), segs.end());
    int Pidx = 0;
    set<std::pair<int, int>> PQ;
    for (int i = 0, line_x = 1; line_x <= label_x; line_x++) {
        while (Pidx < N && P[Pidx].x <= line_x) {
            int intersect = query(P[Pidx].y);
            if (intersect%2 == 0)
                outer_val += P[Pidx].v;
            Pidx++;
        }
        while (!PQ.empty() && PQ.begin()->first <= line_x)
            modify(PQ.begin()->second, -1, label_y), PQ.erase(PQ.begin());
        while (i < segs.size() && segs[i].xl == line_x) {
            modify(segs[i].y, 1, label_y);
            PQ.insert(make_pair(segs[i].xr, segs[i].y));
            i++;
        }
    }
    printf("%lld\n", outer_val);
}
int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &P[i].x, &P[i].y);
            P[i].v = i+1;
        }
        
        for (int i = 0; i < M; i++)
            scanf("%d %d", &D[i].x, &D[i].y);
        
        solve(N, M);
    }
    return 0;
}