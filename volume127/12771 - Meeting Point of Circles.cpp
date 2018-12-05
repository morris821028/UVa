#include <bits/stdc++.h>
using namespace std;

const int MAXN = 128;
const float eps = 1e-6;
struct Circle {
	float x, y, r;
	Circle() {}
	Circle(float x, float y, float r):
		x(x), y(y), r(r) {}
};

struct Pt {
    float x, y;
    Pt() {}
    Pt(float a, float b): x(a), y(b) {}
    Pt operator-(const Pt &a) const { return Pt(x - a.x, y - a.y); }
    Pt operator+(const Pt &a) const { return Pt(x + a.x, y + a.y); }
    Pt operator*(const float a) const { return Pt(x * a, y * a);  }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)	return x < a.x;
        if (fabs(y - a.y) > eps)	return y < a.y;
        return false;
    }
    bool operator==(const Pt &a) const {
        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }
    void println() const {
    	printf("(%lf, %lf)\n", x, y);
    }
};

float rand_float() {
	return (rand() % 32767) / 32767.0;
}
static Circle C[MAXN];
static Pt loc[MAXN];
static int n;
float min_time(Pt p, float limit) {
	float ret = 0;
	for (int i = 0; i < n; i++) {
		float dx = C[i].x-p.x;
		float dy = C[i].y-p.y;
		float d = sqrt(dx*dx + dy*dy);
		if (d >= C[i].r)
			ret = max(ret, d - C[i].r);
		else
			ret = max(ret, C[i].r - d);
		if (ret > limit)
			return ret;
	}
	return ret;
}

const int E_CNT = 50;
const int T_CNT = 50;
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			float x, y, r;
			scanf("%f %f %f", &x, &y, &r);
			C[i] = Circle(x, y, r);
		}

		float lx, ly, rx, ry;
		lx = C[0].x - C[0].r, rx = C[0].x + C[0].r;
		ly = C[0].y - C[0].r, ry = C[0].y + C[0].r;
		for (int i = 1; i < n; i++) {
			lx = min(lx, C[i].x - C[i].r), rx = max(rx, C[i].x + C[i].r);
			ly = min(ly, C[i].y - C[i].r), ry = max(ry, C[i].y + C[i].r);
		}
		
		float h[MAXN];
		float step = max(rx-lx, ry-ly);
		for (int i = 0; i < E_CNT; i++) {
			loc[i] = Pt(rand_float()*(rx-lx)+lx, rand_float()*(ry-ly)+ly);
			h[i] = min_time(loc[i], 666666);
		}
		while (step > 1e-6) {
			for (int i = 0; i < E_CNT; i++) {
				for (int it = 0; it < T_CNT; it++) {
					float tx = loc[i].x + step*2*rand_float() - step;
					float ty = loc[i].y + step*2*rand_float() - step;
					float th = min_time(Pt(tx, ty), h[i]);
					if (th < h[i])
						loc[i].x = tx, loc[i].y = ty, h[i] = th;
				}
			}
			step *= 0.6;
		}
		
		float ret = max(rx-lx, ry-ly);
		for (int i = 0; i < E_CNT; i++)
			ret = min(ret, h[i]);
		printf("%.12f\n", ret);
	}
	return 0;
}

/*
2
2
0 0 1
10 0 1
2
1 0 10
-1 0 10
*/
