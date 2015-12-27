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
 
#define RANDPT 500000
#define MAXDIS 1e+9
		double r2 = r*2, rq2 = r*r;
        int cnt[16] = {};
        for (int i = RANDPT-1; i >= 0; i--) {
            Point3D s = {random()*r2-r, random()*r2-r, random()*r2-r};
            if (s.x*s.x + s.y*s.y + s.z*s.z > rq2) {
            	i++;
                continue;
            }
            double dist = MAXDIS, tmp;
            int u = 0;
#define distance(i) (p[i].x-s.x)*(p[i].x-s.x)+(p[i].y-s.y)*(p[i].y-s.y)+(p[i].z-s.z)*(p[i].z-s.z)
            for (int j = 0; j < n; j++) {
                tmp = distance(j);
                if (tmp < dist)
                    dist = tmp, u = j;
            }
            cnt[u]++;
        }
         printf("Case #%d:\n", ++cases);
        for (int i = 0; i < n; i++)
            printf("%.0lf\n", cnt[i] * 100.f / RANDPT);
    }
    return 0;   
}


