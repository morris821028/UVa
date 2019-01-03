#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
struct Pt {
    float x, y;
    int id;
    Pt() {}
    Pt(float a, float b, int id): x(a), y(b), id(id) {}
    Pt operator-(const Pt &a) const { return Pt(x - a.x, y - a.y, id); }
    Pt operator+(const Pt &a) const { return Pt(x + a.x, y + a.y, id); }
    Pt operator*(const double a) const { return Pt(x * a, y * a, id);  }
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

double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}

struct HalfAngleCmp {
	Pt o;
	HalfAngleCmp(Pt o): o(o) {}
    bool operator()(const Pt &x, const Pt &y) const {
        return cross(o, x, y) < 0;
    }
};

const int MAXN = 10005;
void find_partition(Pt A[], int an, Pt B[], int bn) {
	assert(an%2 == 1 && bn%2 == 1);
	static int match[MAXN];
	memset(match, -1, sizeof(match[0])*an);
	for (int i = 0; i < an; i++) {
		nth_element(B, B+bn/2, B+bn, HalfAngleCmp(A[i]));
//		printf("---- %d %d\n", A[i].id, B[bn/2].id);
		match[A[i].id] = B[bn/2].id;
	}
	for (int i = 0; i < bn; i++) {
		nth_element(A, A+an/2, A+an, HalfAngleCmp(B[i]));
//		printf("++++ %d %d\n", A[an/2].id, B[i].id);
		if (match[A[an/2].id] == B[i].id) {
			printf("%d %d\n", A[an/2].id, B[i].id);
			return;
		}
	}
	puts("-1");
}
int main() {
	int cases = 0;
	int n;
	Pt A[MAXN], B[MAXN];
	while (scanf("%d", &n) == 1 && n) {
		int an = 0, bn = 0;
		double x, y;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &x, &y);
			if (x < 0)
				A[an] = Pt(x, y, an), an++;
			else
				B[bn] = Pt(x, y, bn), bn++;
		}

		printf("Case %d: ", ++cases);
		find_partition(A, an, B, bn);
	}
	return 0;
}

/*
8
2397.3580 -1218.2430
3882.3760 -1892.8990
5038.0060 110.7790
4151.7250 2203.4090
1244.6460 3047.0100
-2567.4500 4835.3570
2964.6920 1447.6210
3742.6950 -1039.6250
8
3533.6490 -610.2480
-2707.0150 -3010.9940
-3440.8270 4392.1250
-54.2620 2227.8020
90.9070 2297.0630
-3236.5420 2868.4760
-1882.3930 -521.8910
3031.9350 -2618.9450
0
*/
