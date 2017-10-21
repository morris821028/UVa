// I think it's a wrong solution, because the testcase on the end of code
#include <bits/stdc++.h> 
using namespace std;

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
    bool operator!=(const Pt &a) const {
    	return !(a == *this);
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
    void read() {
        scanf("%lf %lf", &x, &y);
    }
};

const double pi = acos(-1);
int cmpZero(double v) {
    if (fabs(v) > eps) return v > 0 ? 1 : -1;
    return 0;
}
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

struct Pt3D {
	double x, y, z;
	Pt3D(double x=0, double y=0, double z=0):
		x(x), y(y), z(z) {}
	Pt3D operator-(const Pt3D &a) const {
        return Pt3D(x - a.x, y - a.y, z - a.z);
    }
    Pt3D operator+(const Pt3D &a) const {
        return Pt3D(x + a.x, y + a.y, z + a.z);
    }
    Pt3D operator*(const double a) const {
        return Pt3D(x * a, y * a, z * a);
    }
	void read() {
		scanf("%lf %lf %lf", &x, &y, &z);
	}
};
Pt3D cross(Pt3D a, Pt3D b) {
	return Pt3D(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}
double dot(const Pt3D &a, const Pt3D &b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
struct Triangle3D {
	Pt3D pt[3];
	Pt3D normal;
	void read() {
		for (int i = 0; i < 3; i++)
			pt[i].read();
		normal = cross(pt[1]-pt[0], pt[2]-pt[0]);
	}
};
// triangle and point
int inner(Triangle3D &A, Pt3D p) {
	int s[3];
	s[0] = cmpZero(dot(cross(A.pt[2]-A.pt[0], p-A.pt[0]),
				cross(p-A.pt[0], A.pt[1]-A.pt[0])));
	s[1] = cmpZero(dot(cross(A.pt[0]-A.pt[1], p-A.pt[1]),
				cross(p-A.pt[1], A.pt[2]-A.pt[1])));
	s[2] = cmpZero(dot(cross(A.pt[1]-A.pt[2], p-A.pt[2]),
				cross(p-A.pt[2], A.pt[0]-A.pt[2])));
	return s[0] == s[1] && s[1] == s[2];
}

// triangle and segment
int intersection(Triangle3D &A, Pt3D p, Pt3D q) {
	// parallel plane
	if (cmpZero(dot(A.normal, q-p)) == 0)
		return 0;
	double t = dot(A.normal, A.pt[0]-p) / dot(A.normal, q-p);
	if (t < 0 || t-1 > 0)
		return 0;
	Pt3D r = p + (q-p)*t;
	return inner(A, r);
}

// two triangle in 3D
int intersection(Triangle3D A, Triangle3D B) {
	for (int i = 0; i < 3; i++) {
		if (intersection(A, B.pt[i], B.pt[(i+1)%3]))
			return 1;
		if (intersection(B, A.pt[i], A.pt[(i+1)%3]))
			return 1;
	}
	return 0;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		Triangle3D A, B;
		A.read();
		B.read();
		int ret = intersection(A, B);
		puts(ret ? "1" : "0");
	}
	return 0;
}
/*
2
0.366955 0.566515 0.398724
0.573168 0.175512 0.873745
0.705588 0.374035 0.072390
0.292306 0.515061 0.371929
0.623737 0.169012 0.514115
0.839076 0.717612 0.255867
0.039521 0.379528 0.617084
0.759484 0.836268 0.097446
0.594165 0.484085 0.191534
0.283731 0.896054 0.182867
0.443800 0.472579 0.899808
0.473342 0.573901 0.769219

1
0 0 0
2 3 0
4 0 0
0 2 0
4 2 0
2 -1 0
*/
