#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point3D {
	double x, y, z;
} Point3D;

double random() {
	return 1.f * rand() / RAND_MAX;
}
int main() {
	int cases = 0;
	int n, r;
	while (scanf("%d %d", &r, &n) == 2) {
		Point3D p[16];
		for (int i = 0; i < n; i++)
			scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);
		
		const int RANDPT = 1000000;
		int ect = 0, cnt[16] = {};
		int chunk = 8;
        #pragma omp parallel for schedule(dynamic, chunk)
		for (int it = 0; it < 10; it++) {
			int tect = 0, tcnt[16] = {};
			for (int i = 0; i < RANDPT; i++) {
	            Point3D s = {random()*2-1, random()*2-1, random()*2-1};
	            if (s.x*s.x + s.y*s.y + s.z*s.z > 1.f)
	            	continue;
	        	s.x *= r, s.y *= r, s.z *= r;
	            tect++;
	            double dist, tmp;
	            int u = 0;
#define distance(i) (p[i].x-s.x)*(p[i].x-s.x)+(p[i].y-s.y)*(p[i].y-s.y)+(p[i].z-s.z)*(p[i].z-s.z)
	            dist = distance(0);
	            for (int j = 1; j < n; j++) {
	                tmp = distance(j);
	                if (tmp < dist)
	                    dist = tmp, u = j;
	            }
	            tcnt[u]++;
	        }
	        #pragma omp critical
	        {
	        	ect += tect;
	        	for (int i = 0; i < n; i++)
	        		cnt[i] += tcnt[i];
			}
		}

 		printf("Case #%d:\n", ++cases);
        for (int i = 0; i < n; i++)
            printf("%.0lf\n", cnt[i] * 100.f / ect);
	}
	return 0;	
}
/*
5 1
0 0 0

5 2
0 0 0
4 0 0
*/
