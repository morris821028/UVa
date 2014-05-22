#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;
struct Point {
	long long x, y;
	Point(long long a = 0, long long b = 0):
		x(a), y(b) {}
	Point operator-(const Point& z) {
		return Point(x - z.x, y - z.y);
	}
};
Point D[65536];
Point R[65536];
int N;
long long cross(Point a, Point b) {
	return a.x * b.y - a.y * b.x;
}
long long dist(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
double dist2(Point a, double idx) {
	double x, y;
	int i = (int)floor(idx);
	double da = dist(a, D[i]), db = dist(a, D[i+1]);
	return da + (db - da) * (idx - i);
}
void ternary_search(int n, double l, double r) {
	double mid, midmid;
	double md, mmd;
	if(l > r)	return;
#ifdef DEBUG
	printf("search %d in [%lf %lf]\n", n, l, r);
#endif
	mid = (l + r)/2;
	while(fabs(l - r) > 1e-1) {
		mid = (l + r)/2;
		midmid = (mid + r)/2;
		// md = dist(D[n], D[mid]);
		// mmd = dist(D[n], D[midmid]);
		md = dist2(D[n], mid);
		mmd = dist2(D[n], midmid);
#ifdef DEBUG
	if(n == 8) {
		printf("[%lf %lf] %lf %lf, %lf %lf\n", l, r, mid, md, midmid, mmd);
	}
#endif
		//if(md > R[n].x || (md == R[n].x && mid < R[n].y))
		//	R[n].x = md, R[n].y = mid;
		//if(mmd > R[n].x || (mmd == R[n].x && midmid < R[n].y))
		//	R[n].x = mmd, R[n].y = midmid;
		if(md >= mmd) {
			r = midmid;
		} else {
			l = mid;
		}
	}
	long long idx = ((long long) round(mid)) % N;
	long long dd = dist(D[n], D[idx]);
	if(dd > R[n].x || (dd == R[n].x && idx < R[n].y))
		R[n].x = dd, R[n].y = idx;
#ifdef DEBUG
	printf("%lf %lf %lf\n", mid, l, r);
	printf("search result = [%lld %lld]\n", R[n].x, R[n].y);
#endif
}
void singleUpdate(int n, int s) {
	long long idx = s;
	long long dd = dist(D[n], D[s]);
	if(dd > R[n].x || (dd == R[n].x && idx < R[n].y))
		R[n].x = dd, R[n].y = idx;
}
int main() {	
	freopen("out.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout);  
	while(scanf("%d", &N) == 1 && N) {
		for(int i = 0; i < N; i++) {
			long long x, y;
			scanf("%lld %lld", &x, &y);
			D[i] = Point(x, y);
			D[N + i] = D[i];
			R[i] = Point(0, i);
		}
		
		for(int i = 0, j = 0; i < N; i++) {
			int time = 0;
			while(cross(D[(i + 1)%N] - D[i], D[(j + 1 + N)%N] - D[j]) >= 0) {
				j = (j + 1)%N;
			}
			if(j > i) {
				ternary_search(i, i + 1, j - 1);
				ternary_search(i, j + 1, N - 1);
				ternary_search(i, 0, i - 1);
			} else {
				ternary_search(i, j + 1, i - 1);
				ternary_search(i, 0, j - 1);
				ternary_search(i, i + 1, N - 1);
			}
			singleUpdate(i, j);
#ifdef DEBUG
			if(i == 8) {
				long long a, b, c;
				a = D[i].y - D[(i + 1)%N].y;
				b = D[(i + 1)%N].x - D[i].x;
				c = - (a * D[i].x + b * D[i].y);
				for(int j = 0; j < N; j++) {
					double dist = 0;
					dist = fabs(a * D[j].x + b * D[j].y + c) / hypot(a,  b);
					printf("%10.3lf [%lld %lld]\n", dist, D[j].x, D[j].y);
				}
			}
			printf("TOP (%lld %lld)(%lld %lld) -- (%lld %lld)\n\n", D[i].x, D[i].y, 
			D[(i + 1)%N].x, D[(i + 1)%N].y, D[j].x, D[j].y);
#endif
		}
		for(int i = 0; i < N; i++) {
			long long mx = 0, r = i;
			/*for(int j = 0; j < N; j++) {
				if(dist(D[i], D[j]) > mx)
					mx = dist(D[i], D[j]), r = j;
			}*/
			//printf("%lld\n", r + 1);
			//printf("%lld -- %lld -- %lld -- %lld [i = %d] \n", r, mx, R[i].x, R[i].y, i);
			//if(R[i].y != r)
			//	puts("wryyyyyyyyyyyy");
			/*if(i == 11) {
				for(int j = 0; j < N; j++)
					printf("[i = %2d] %10lld [%lld, %lld]\n", j, dist(D[i], D[j]), D[j].x, D[j].y);
			}*/
			printf("%lld\n", R[i].y + 1);
		}
	}
	return 0;
}
/*
5
0 0
4 2
2 4
-2 4
-4 2
3
0 0
1 0
0 10
8
3 2
3 -2
2 -3
-2 -3
-3 -2
-3 2
-2 3
2 3
18
1 7528
230 4100
685 2104
1626 537
1905 135
15161 12
25154 28
31805 44
32519 6826
32642 9780
32762 20868
32755 29778
31717 31192
31328 31469
29206 32760
10227 32668
253 32513
41 22812
16
57 26065
178 5836
233 2013
252 869
405 2
17671 70
24347 117
31963 438
32690 879
32717 13093
32733 27258
32506 32687
16861 32646
5286 32604
2252 32579
213 31539
21
8 22713
76 19609
269 11641
566 3396
727 929
2511 704
7452 129
10805 42
16646 33
22126 219
29849 565
32284 2252
32683 3309
32703 8397
32701 10668
32597 27777
32567 28654
32101 32666
17692 32745
341 32766
51 32749
16
30 304
18328 143
26602 181
32594 407
32705 11719
32676 24934
32617 25310
31567 29762
31388 30243
30141 32349
29614 32691
18075 32734
6803 32663
1595 32559
159 31372
83 21756
*/
