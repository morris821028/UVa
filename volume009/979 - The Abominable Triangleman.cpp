#include <stdio.h> 
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define eps 1e-6
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x-a.x) > eps)
            return x < a.x;
        if(fabs(y-a.y) > eps)
        	return y < a.y;
        return false;
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
	Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator/(const double a) const {
        return Pt(x /a, y /a);
    }
    Pt operator*(const double a) const {
        return Pt(x *a, y *a);
    }
    int in() {
    	return scanf("%lf %lf", &x, &y) == 2;
    }
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double dist2(Pt a, Pt b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
double length(Pt a) {
	return hypot(a.x, a.y);
}
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
double angle(Pt a, Pt b) {
	return acos(dot(a, b) / length(a) / length(b));
}
Pt rotateRadian(Pt a, double radian) {
	double x, y;
	x = a.x * cos(radian) - a.y * sin(radian);
	y = a.x * sin(radian) + a.y * cos(radian);
	return Pt(x, y);
}

int main() {
	Pt A, B, C, D[2048];
	int N, cases = 0;
	while(A.in() && B.in() && C.in()) {
		scanf("%d", &N);
		set<Pt> S;
		for(int i = 0; i < N; i++)
			D[i].in(), S.insert(D[i]);
		if(cases++)	puts("");
		double AB = dist2(A, B), BC = dist2(B, C), sqrAB = dist(A, B), sqrBC = dist(B, C);
		double aABC = angle(A - B, C - B);
		sort(D, D + N);
		
		vector<Pt> ret;
		for(int i = 0; i < N; i++) {
			for(int j = i+1; j < N; j++) {
				if(AB < (D[j].x - D[i].x) * (D[j].x - D[i].x))
					break;
				if(fabs(AB - dist2(D[i], D[j])) < eps) {
//					printf("%lf %lf %lf %lf\n", D[i].x, D[i].y, D[j].x, D[j].y);
					Pt vBC, tc;
					vBC = rotateRadian(D[i] - D[j], +aABC) * (sqrBC/sqrAB);
					tc = D[j] + vBC;
					if(S.find(tc) != S.end()) {
						ret.push_back(tc);
						ret.push_back(D[i]);
						ret.push_back(D[j]);
					}
					
					vBC = rotateRadian(D[i] - D[j], -aABC) * (sqrBC/sqrAB);
					tc = D[j] + vBC;
					if(S.find(tc) != S.end()) {
						ret.push_back(tc);
						ret.push_back(D[i]);
						ret.push_back(D[j]);
					}					
					
					vBC = rotateRadian(D[j] - D[i], +aABC) * (sqrBC/sqrAB);
					tc = D[i] + vBC;
					if(S.find(tc) != S.end()) {
						ret.push_back(tc);
						ret.push_back(D[i]);
						ret.push_back(D[j]);
					}
					
					vBC = rotateRadian(D[j] - D[i], -aABC) * (sqrBC/sqrAB);
					tc = D[i] + vBC;
					if(S.find(tc) != S.end()) {
						ret.push_back(tc);
						ret.push_back(D[i]);
						ret.push_back(D[j]);
					}
				}
			}
		}
		if(ret.size()) {
			sort(ret.begin(), ret.end());
			for(int i = 0; i < 3; i++) {
				printf("%.0lf %.0lf\n", ret[i].x, ret[i].y);
			}
		}
	}
	return 0;
}
/*
5 15
8 5
20 10
6
5 17
5 20
20 5
10 5
15 20
15 10
*/
