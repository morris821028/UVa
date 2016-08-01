// dp, slower, TLE ! 
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
#include <assert.h>
#include <queue>
#include <algorithm>
using namespace std;

#define MAXV 0x3f3f3f3f
#define MAXE 65536
#define MAXC 65536
#define MAXR 65536
class DLX {
public:
    struct DacingLinks {
        int left, right;
        int up, down;
        int ch, rh;
        int data; // extra info
    } DL[MAXE];
    int s[MAXC], o[MAXR], head, size, Ans, sAns, findflag;
    void Remove(int c) {
        static int i;
        for(i = DL[c].down; i != c; i = DL[i].down) {
            DL[DL[i].right].left = DL[i].left;
            DL[DL[i].left].right = DL[i].right;
            s[DL[i].ch]--;
        }
    }
    void Resume(int c) {
        static int i;
        for(i = DL[c].down; i != c; i = DL[i].down) {
            DL[DL[i].right].left = i;
            DL[DL[i].left].right = i;
            s[DL[i].ch]++;
        }
    }
    int used[MAXC] = {};
    int H() {
        static int c, ret, i, j, time = 0;
        for(c = DL[head].right, ++time, ret = 0; c != head; c = DL[c].right) {
            if(used[c] != time) {
                ret ++, used[c] = time;
                for(i = DL[c].down; i != c; i = DL[i].down)
                    for(j = DL[i].right; j != i; j = DL[j].right)
                        used[DL[j].ch] = time;
            }
        }
        return ret;
    }
    void DFS(int k) {
        if(k + H() >= Ans || Ans <= sAns) return;
        if(DL[head].right == head) {
            Ans = min(Ans, k);
            return;
        }
        int t = MAXV, c = 0, i, j;
        for(i = DL[head].right; i != head; i = DL[i].right) {
            if(s[i] < t) {
                t = s[i], c = i;
            }
        }
        for(i = DL[c].down; i != c; i = DL[i].down) {
            o[k] = i;
            Remove(i);
            for(j = DL[i].right; j != i; j = DL[j].right) Remove(j);
            DFS(k+1);
            for(j = DL[i].left; j != i; j = DL[j].left) Resume(j);
            Resume(i);
            if (findflag) break;
        }
    }
    int new_node(int up, int down, int left, int right) {
        assert(size < MAXE);
        DL[size].up = up, DL[size].down = down;
        DL[size].left = left, DL[size].right = right;
        DL[up].down = DL[down].up = DL[left].right = DL[right].left = size;
        return size++;
    }
    void addrow(int n, int Row[], int data) {
        int a, r, row = -1, k;
        for(a = 0; a < n; a++) {
            r = Row[a];
            DL[size].ch = r, s[r]++;
            DL[size].data = data;
            if(row == -1) {
                row = new_node(DL[DL[r].ch].up, DL[r].ch, size, size);
                DL[row].rh = a;
            }else {
                k = new_node(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row);
                DL[k].rh = a;
            }
        }
    }
    void init(int m) {
        size = 0, sAns = -1;
        head = new_node(0, 0, 0, 0);
        int i;
        for(i = 1; i <= m; i++) {
            new_node(i, i, DL[head].left, head);
            DL[i].ch = i, s[i] = 0;
        }
    }
} dlx;

#define eps 1e-6
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
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
    bool operator==(const Pt &a) const {
        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)
            return x < a.x;
        if (fabs(y - a.y) > eps)
            return y < a.y;
        return false;
    }
    double length() {
        return hypot(x, y);
    }
    double length2() {
        return x*x + y*y;
    }
    void read() {
        scanf("%lf %lf", &x, &y);
    }
};
double dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
double cross2(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
int between(Pt a, Pt b, Pt c) {
    return dot(c - a, b - a) >= -eps && dot(c - b, a - b) >= -eps;
}
int onSeg(Pt a, Pt b, Pt c) {
    return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
struct Seg {
    Pt s, e;
    double angle;
    int label;
    Seg(Pt a = Pt(), Pt b = Pt(), int l=0):s(a), e(b), label(l) {
        // angle = atan2(e.y - s.y, e.x - s.x);
    }
    bool operator<(const Seg &other) const {
        if (fabs(angle - other.angle) > eps)
            return angle > other.angle;
        if (cross(other.s, other.e, s) > -eps)
            return true;
        return false;
    }
    bool operator!=(const Seg &other) const {
        return !((s == other.s && e == other.e) || (e == other.s && s == other.e));
    }
};
Pt getIntersect(Seg a, Seg b) {
    Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
double getAngle(Pt va, Pt vb) { // segment, not vector
    return acos(dot(va, vb) / va.length() / vb.length());
}
double distSeg2Point(Pt a, Pt b, Pt p) {
    Pt c, vab;
    vab = a - b;
    if (between(a, b, p)) {
        c = getIntersect(Seg(a, b), Seg(p, Pt(p.x+vab.y, p.y-vab.x)));
        return (p - c).length();
    }
    return min((p - a).length(), (p - b).length());
}
Pt rotateRadian(Pt a, double radian) {
    double x, y;
    x = a.x * cos(radian) - a.y * sin(radian);
    y = a.x * sin(radian) + a.y * cos(radian);
    return Pt(x, y);
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}
int cmpZero(double x) {
    if (fabs(x) < eps)  return 0;
    return x < 0 ? -1 : 1;
}
Pt projectLine(Pt as, Pt ae, Pt p) {
    double a, b, c, v;
    a = as.y - ae.y, b = ae.x - as.x;
    c = - (a * as.x + b * as.y);
    v = a * p.x + b * p.y + c;
    return Pt(p.x - v*a / (a*a+b*b), p.y - v*b/ (a*a+b*b));
}
const double pi = acos(-1);

Pt circle(Pt &a, Pt &b, Pt &c) {
    Pt ab, ac, vab, vac;
   	ab = (a + b) * 0.5, ac = (a + c) * 0.5;
   	vab.x = a.y - b.y, vab.y = b.x - a.x;
   	vac.x = a.y - c.y, vac.y = c.x - a.x;
    return getIntersect(Seg(ab, ab+vab), Seg(ac, ac + vac));
}

const int MAXN = 18;
Pt D[MAXN];

bool cmp(pair<double, int> a, pair<double, int> b) {
	if (a.second != b.second)
		return a.second < b.second;
	return cmpZero(a.first - b.first) < 0;
}
vector< pair<double, int> > makeAllCircle(Pt D[], int N) {
	vector< pair<double, int> > ret;
	Pt c;
	double cr;
	for (int i = 0; i < N; i++) {
		// one point
		ret.push_back(make_pair(0, 1<<i)); 
		// two point
		for (int j = i+1; j < N; j++) {
			c = (D[i] + D[j]) * 0.5;
			cr = (D[i] - c).length2();
			int mask = 0;
			for (int i = 0; i < N; i++) {
				if (cmpZero((c - D[i]).length2() - cr) <= 0)
					mask |= 1<<i;
			}
			ret.push_back(make_pair(cr, mask));
			// tree point
			for (int k = j+1; k < N; k++) {
				if (cmpZero(cross(D[i], D[j], D[k])) == 0) 
					continue;
				c = circle(D[i], D[j], D[k]);	
				cr = (D[i] - c).length2();
				mask = 0;
				for (int i = 0; i < N; i++) {
					if (cmpZero((c - D[i]).length2() - cr) <= 0)
						mask |= 1<<i;
				}
				ret.push_back(make_pair(cr, mask));
			}
		}
	}
	
	sort(ret.begin(), ret.end(), cmp);
	int m = 0;
	for (int i = 1; i < ret.size(); i++) {
		if (ret[i].second != ret[m].second)
			ret[++m] = ret[i];
	}
	ret.resize(m+1);
	return ret;
}
int A[65536];
int random(vector< pair<double, int> > &circles, int N, int R) {
	for (int i = 0; i < circles.size(); i++)
		A[i] = i;
	double c = 1e+20, cc;
	int r = circles.size()-1;
	for (int it = 0; it < 64; it++) {
		random_shuffle(A, A+circles.size());
		int mask = 0;
		cc = 0;
		for (int j = 0; j < R; j++) {
			mask |= circles[A[j]].second;
			cc = max(cc, circles[A[j]].first);
		}
		if (mask == (1<<N)-1 && cc < c) {
			c = cc;
			int rm = 0;
			for (int j = 0; j < R; j++)
				rm = max(rm, A[j]);
			r = min(r, rm);
		}
	}
	return r;
}
int main() {
    int testcase, cases = 0;
    int N, R;
    scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%d %d", &N, &R);
    	for (int i = 0; i < N; i++)
    		D[i].read();
    	
		vector< pair<double, int> > circles = makeAllCircle(D, N);
		    	
		sort(circles.begin(), circles.end());
				
		int row[32], rn;
		int l = 0, r = circles.size()-1, mid;
		r = random(circles, N, R);
		double ret = circles[r].first;
		while (l <= r) {
			mid = (l + r)/2;
			
			dlx.init(N);
			for (int i = 0; i <= mid; i++) {
				int mask = circles[i].second;
				rn = 0;
				for (int j = 0; j < N; j++) {
					if ((mask>>j)&1)
						row[rn++] = j+1;
				}
				dlx.addrow(rn, row, i);
			}
			dlx.Ans = R+1, dlx.sAns = R;
			dlx.DFS(0);
			if (dlx.Ans <= R)
				r = mid - 1, ret = circles[mid].first;
			else
				l = mid + 1;
		}		 
		printf("Case %d: %.2lf\n", ++cases, sqrt(ret));
    }
    return 0;
}

/*

10
10 2
3 16 8 2 1 19 1 4 1 14 2 13 8 11 5 3 11 17 12 19
9 4
4 9 8 10 7 6 1 8 17 3 1 17 18 3 1 3 3 16
8 4
5 14 3 15 18 9 15 19 3 12 3 5 10 9 14 4
2 2
3 10 18 5
9 2
16 13 17 15 18 2 7 13 19 10 9 10 17 14 4 19 18 1
1 1
8 7
8 2
16 19 11 15 2 0 0 11 6 5 2 11 14 6 8 15
10 9
1 14 16 12 11 18 13 12 3 7 16 19 14 15 18 7 5 9 13 3
7 1
1 18 19 7 7 16 11 7 0 15 12 16 17 7
4 4
5 13 17 7 8 14 4 3


3

2 1
0 0 10 0

6 2
0 0 1 1 2 2 10 10 10 11 10 12

4 2
0 0 10 0 5 10 1000 1000
*/
