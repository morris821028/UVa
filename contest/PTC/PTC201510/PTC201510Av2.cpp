#include <stdio.h> 
#include <string.h>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
const int MAXN = 131072;
class SegmentTree {
public:
    struct Node {
        int cover;				// #cover
        int L, R;			// value in real line, cover [L, R]
        int clen;			// cover length
        void init(int a = 0, int b = 0, int c = 0, int d = 0) {
            cover = a, L = b, R = c, clen = d;
        }
    } nodes[MAXN];
    int Y[MAXN];
    void pushDown(int k, int l, int r) {

    }
    void pushUp(int k, int l, int r) {
        if (nodes[k].cover > 0) {
            nodes[k].clen = nodes[k].R - nodes[k].L;
        } else {
            if (l == r)
                nodes[k].clen = 0;
            else
                nodes[k].clen = nodes[k<<1].clen + nodes[k<<1|1].clen;
        }
    }
    void build(int k, int l, int r) { 
        nodes[k].init(0, Y[l], Y[r+1], 0);
        if (l == r)
            return ;
        int mid = (l + r)/2;
        build(k<<1, l, mid);
        build(k<<1|1, mid+1, r);
        pushUp(k, l, r);
    } 
    // operator, add
    void addUpdate(int k, int l, int r, int val) {
        nodes[k].cover += val;
        if (nodes[k].cover > 0) {
            nodes[k].clen = nodes[k].R - nodes[k].L;
        } else {
            if (l == r)
                nodes[k].clen = 0;
            else
                nodes[k].clen = nodes[k<<1].clen + nodes[k<<1|1].clen;
        }
    }
    void add(int k, int l, int r, int x, int y, int val) {
        if (x <= l && r <= y) {
            addUpdate(k, l, r, val);
            return;
        }
        pushDown(k, l, r);
        int mid = (l + r)/2;
        if (x <= mid)
            add(k<<1, l, mid, x, y, val);
        if (y > mid)
            add(k<<1|1, mid+1, r, x, y, val);
        pushUp(k, l, r);
    }
    // query 
    long long r_sum;
    void qinit() {
        r_sum = 0;
    }
    void query(int k, int l, int r, int x, int y) {
        if (x <= l && r <= y) {
            r_sum += nodes[k].clen;
            return ;
        }
        pushDown(k, l, r);
        int mid = (l + r)/2;
        if (x <= mid)
            query(k<<1, l, mid, x, y);
        if (y > mid)
            query(k<<1|1, mid+1, r, x, y);
        pushUp(k, l, r);
    }
} tree;
struct Event {
    long long x, yl, yr;
    int val;
    Event(long long a = 0, long long b = 0, long long c = 0, int d = 0):
    x(a), yl(b), yr(c), val(d) {}
    bool operator<(const Event &a) const {
        return x < a.x;
    }
};

const int MAXD = 32767;
int Lx[MAXD], Ly[MAXD], Rx[MAXD], Ry[MAXD];

long long areaCoverAll(int N, int Lx[], int Ly[], int Rx[], int Ry[]) {
    vector<Event> events;
    vector<int> VY;
    map<int, int> RY;
    for (int i = 0; i < N; i++) {
        int x1, x2, y1, y2;
        x1 = Lx[i], x2 = Rx[i];
        y1 = Ly[i], y2 = Ry[i];
        if (x1 < x2 && y1 < y2) {
            events.push_back(Event(x1, y1, y2,  1));
            events.push_back(Event(x2, y1, y2, -1));
            VY.push_back(y1), VY.push_back(y2);
        }
    }
    
    sort(VY.begin(), VY.end());	
    VY.resize(unique(VY.begin(), VY.end()) - VY.begin());
    
    for (int i = 0; i < VY.size(); i++) {
        tree.Y[i] = VY[i];
        RY[VY[i]] = i;
    }
                
    if (VY.size() < 2)	
        return 0;
    tree.build(1, 0, VY.size()-2);
    
    sort(events.begin(), events.end());
    long long area = 0, prevX = 0;
    for (int i = 0, j; i < events.size(); ) {		
        if (i > 0) {
            tree.qinit();
            tree.query(1, 0, VY.size()-2, 0, VY.size()-2);
            area += (events[i].x - prevX) * tree.r_sum;
        }
        j = i;
        while (j < events.size() && events[j].x <= events[i].x) {
            tree.add(1, 0, VY.size()-2, RY[events[j].yl], RY[events[j].yr] - 1, events[j].val);
            j++;
        }
        prevX = events[i].x;
        i = j;
    }
    return area;
}
int main() {
    int testcase, cases = 0;
    int N;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
        	scanf("%d %d %d %d", &Lx[i], &Ly[i], &Rx[i], &Ry[i]);
        	if (Lx[i] > Rx[i])	swap(Lx[i], Rx[i]);
        	if (Ly[i] > Ry[i])	swap(Ly[i], Ry[i]);
        }
        long long area = areaCoverAll(N, Lx, Ly, Rx, Ry);
        printf("%lld\n", area);
    }
    return 0;
}
