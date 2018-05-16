#include <bits/stdc++.h> 
using namespace std;
const double eps = 1e-15;
struct Circle {
    double x, y, r;
    int read() {
        return scanf("%lf %lf %lf", &x, &y, &r) == 3;
    }
};
struct Pt {
    double x, y;
    bool operator<(const Pt other) const {
        if (fabs(x-other.x) < eps)
            return y < other.y;
        return x < other.x;
    }
};
int intersection_circle(Circle A, Circle B, Pt v[]) { // Pt v[] result buffer
    double disAB = sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
    if (A.r + B.r + eps < disAB || A.r + disAB + eps < B.r || B.r + disAB + eps < A.r) {
        if (disAB < B.r-A.r)
            return 3; //cover all special case
        return -1;
    }
    double vx = B.x - A.x;
    double vy = B.y - A.y;
    if (fabs(disAB-A.r-B.r) < eps || fabs(A.r-disAB-B.r) < eps || fabs(B.r-A.r-disAB) < eps) {
        if (fabs(disAB-A.r-B.r) < eps) {//(A)(B)
        } else {
            if (A.r < B.r) { //((A)B)
                v[0].x = A.x-vx*A.r/(B.r-A.r);
                v[0].y = A.y-vy*A.r/(B.r-A.r);
                return 3; // cover all special case
            } //((B)A)
        }
        return 1;
    }
    double theta = acos((A.r*A.r+disAB*disAB-B.r*B.r)/2/A.r/disAB);
    double rvx, rvy;
    rvx = vx*cos(theta)-vy*sin(theta);
    rvy = vx*sin(theta)+vy*cos(theta);
    v[0].x = A.x+rvx*A.r/disAB;
    v[0].y = A.y+rvy*A.r/disAB;
    rvx = vx*cos(-theta)-vy*sin(-theta);
    rvy = vx*sin(-theta)+vy*cos(-theta);
    v[1].x = A.x+rvx*A.r/disAB;
    v[1].y = A.y+rvy*A.r/disAB;
    return 2;
}

const int MAXN = 105;
const double pi = acos(-1);

int main() {
	int n;
	Circle C[MAXN];
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			C[i].read();

		int ret = 0;
		int visible[MAXN] = {};
		for (int i = 0; i < n; i++) {
			int valid = 1;
			vector<double> A;
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;
				Pt p[2];
				int r = intersection_circle(C[i], C[j], p);
				if (r == 3) {
					if (j > i) {
						valid = 0;
						break;
					} else {
						continue;
					}
				}
				if (r < 2)
					continue;
				double L, R, M;
				L = atan2(p[0].y-C[i].y, p[0].x-C[i].x);
                R = atan2(p[1].y-C[i].y, p[1].x-C[i].x);
                if (L > R)
                    M = L, L = R, R = M;
                M = (L+R)/2;
                double tx = C[i].x+C[i].r*cos(M);
                double ty = C[i].y+C[i].r*sin(M);
                if ((tx-C[j].x)*(tx-C[j].x)+(ty-C[j].y)*(ty-C[j].y) < C[j].r*C[j].r) {
                	A.push_back(L);
                	A.push_back(R);
                } else {
                	A.push_back(-pi);
                	A.push_back(L);
                	A.push_back(R);
                	A.push_back(pi);
                }
			}

			if (valid == 0)
				continue;
			if (A.size() == 0) {
				int cover = 0;
				for (int k = i+1; k < n; k++) {
					if (C[k].r >= C[i].r && (C[i].x-C[k].x)*(C[i].x-C[k].x)+(C[i].y-C[k].y)*(C[i].y-C[k].y) 
						<= (C[i].r-C[k].r)*(C[i].r-C[k].r)) {
						cover = 1;
						break;
					}
				}
				if (!cover)
					visible[i] = 1;
			} else {
				sort(A.begin(), A.end());
				for (int j = 0; j+1 < A.size(); j++) {
					double M = (A[j]+A[j+1])/2;
	            	double tx = C[i].x+C[i].r*cos(M);
	            	double ty = C[i].y+C[i].r*sin(M);
	            	int cover = 0;
	            	for (int k = i+1; k < n; k++) {
	            		if ((tx-C[k].x)*(tx-C[k].x)+(ty-C[k].y)*(ty-C[k].y) <= C[k].r*C[k].r) {
	            			cover = 1;
	            			break;
						}
					}
					if (!cover) {
						visible[i] = 1;
						for (int k = i-1; k >= 0; k--) {
		            		if ((tx-C[k].x)*(tx-C[k].x)+(ty-C[k].y)*(ty-C[k].y) <= C[k].r*C[k].r) {
		            			visible[k] = 1;
								break;
							}
						}
					}
				}
			}
			
		}
		for (int i = 0; i < n; i++)
			ret += visible[i];
		printf("%d\n", ret);
	}
	return 0;
}
/*
3
0 0 0.5
-0.9 0 1.00000000001
0.9 0 1.00000000001
5
0 1 0.5
1 1 1.00000000001
0 2 1.00000000001
-1 1 1.00000000001
0 -0.00001 1.00000000001
5
0 1 0.5
1 1 1.00000000001
0 2 1.00000000001
-1 1 1.00000000001
0 0 1.00000000001
2
0 0 1.0000001
0 0 1
2
0 0 1
0.00000001 0 1
0
*/
