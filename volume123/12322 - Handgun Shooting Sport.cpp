#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;

int main() {
    int n, x1, x2, y1, y2;
    while (scanf("%d", &n) == 1 && n) {
        vector< pair<double, double> > interval;
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            double l = atan2(y1, x1), r = atan2(y2, x2);
            if (l > r)
                swap(l, r);
            interval.push_back(make_pair(l, r));
//            printf("[%lf %lf]\n", l, r);
        }
        sort(interval.begin(), interval.end());
        
        int ret = 0;
#define eps 0
        for (int i = 0, j; i < interval.size(); ) {
            ret++;
            double coverR = interval[i].second;
//            printf("try [%lf %lf]\n", interval[i].first, interval[i].second);
            for (j = i; j < interval.size() && interval[j].first <= coverR + eps; j++)
                coverR = min(coverR, interval[j].second);
            i = j;
        }
        printf("%d\n", ret);
    }
    return 0;
}

/*
 10
 -309 98 -258 204
 -303 83 -251 98
 -218 111 -287 31
 -145 204 -23 257
 -129 272 59 272
 -8 159 74 130
 150 146 68 174
 59 196 128 242
 98 256 241 235
 197 61 173 92
 3
 -100 10 -100 50
 -50 100 50 100
 100 10 100 50
 5
 -100 100 100 100
 -80 120 80 120
 -60 140 60 140
 -40 160 40 160
 -20 180 20 180
 2
 -50 50 0 50
 -10 70 50 70
 2
 -50 50 0 50
 0 70 50 70
 2
 -50 50 0 50
 10 70 50 70
 5
 -4 10 0 2
 5 10 0 1
 -2 1 -3 4
 4 10 2 10
 0 9 -2 9
 0
 */
