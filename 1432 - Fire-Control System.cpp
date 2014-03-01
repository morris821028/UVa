#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
struct Pt {
    int x, y;
    int dist;
    double theta;
    bool operator<(const Pt &a) const {
        if(theta != a.theta)
            return theta < a.theta;
        return dist > a.dist;
    }
};
Pt D[5005];
int mmR[5005];
const double pi = acos(-1);
int main() {
    /*freopen("in.txt", "r+t", stdin);
	freopen("out1.txt", "w+t", stdout);*/
    int N, K;
    int cases = 0;
    int i, j, k;
    while(scanf("%d %d", &N, &K) == 2) {
        if(N == 0 && K == 0)
            break;
        for(i = 0; i < N; i++) {
            scanf("%d %d", &D[i].x, &D[i].y);
            mmR[i] = D[i].x*D[i].x + D[i].y*D[i].y;
            D[i].dist = mmR[i];
            D[i].theta = atan2(D[i].y, D[i].x);
        }
        if(K == 0 || N == 0) {
            printf("Case #%d: 0.00\n", ++cases);
            continue;
        }
        sort(mmR, mmR+N); // sort maybe radius
        sort(D, D+N); // sort by theta
        double ret = 1e+50;
        double area, theta, theta1, theta2;
        /*for(i = 0; i < N; i++) {
            printf("%lf\n", D[i].theta);
        }*/
        int radius = -1;
        for(i = K-1; i < N; i++) {
            if(radius == mmR[i])    continue;
            radius = mmR[i];
            // sweep line algorithm
            int tmpK = 0, pre = 0;
            int idx1 = 0, idx2 = 0, j1, j2;
            int N2 = N*2;
            for(j1 = 0, j2 = 0; j1 < N2; j1++) {
                if(j1 >= N && j2 >= N)  break;
                if(D[idx1].dist <= radius)
                    tmpK++;
                while(tmpK >= K && j2 < j1) {
                    if(tmpK > K && D[idx2].dist <= radius)
                        tmpK--, idx2++, j2++;
                    else if(D[idx2].dist > radius)
                        idx2++, j2++;
                    else
                        break;
                    if(idx2 >= N)   idx2 = 0;
                }
                if(tmpK >= K && j1-j2 < N) {
                    theta1 = D[idx1].theta;
                    theta2 = D[idx2].theta;
                    if(j1 >= N) theta1 += 2*pi;
                    if(j2 >= N) theta2 += 2*pi;
                    else if(theta2 <= theta1)
                        theta = theta1 - theta2;
                    else
                        theta = 2*pi - (theta1 - theta2);
                    //printf("%lf %lf %lf %d %d %d %d %d\n", theta, theta1, theta2, tmpK, j1, j2, idx1, idx2);
                    area = 0.5*radius*theta;
                    ret = min(ret, area);
                }
                idx1++;
                if(idx1 >= N)   idx1 = 0;
            }
        }
        printf("Case #%d: %.2lf\n", ++cases, ret);
    }
    return 0;
}
