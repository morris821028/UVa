#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
#include <map>
#include <vector>
using namespace std;

struct KM {
	int W[105][105], N;
	int mx[105], my[105]; // match arr
	int lx[105], ly[105]; // label arr
	int x[105], y[105]; // used arr
	int hungary(int nd) {
	    int i;
	    x[nd] = 1;
	    for(i = 0; i < N; i++) {
	        if(y[i] == 0 && W[nd][i] == lx[nd]+ly[i]) {
	            y[i] = 1;
	            if(my[i] == -1 || hungary(my[i])) {
	                my[i] = nd;
	                return 1;
	            }
	        }
	    }
	    return 0;
	}
	int run() {
	    int i, j, k, d;
	    memset(mx, -1, sizeof(mx));
	    memset(my, -1, sizeof(my));
	    for (int i = 0; i < N; i++)
	    	lx[i] = -0x3f3f3f3f, ly[i] = 0;
	    for(i = 0; i < N; i++)
	        for(j = 0; j < N; j++)
	            lx[i] = lx[i] > W[i][j] ? lx[i] : W[i][j];
	    for(i = 0; i < N; i++) {
	        while(1) {
	            memset(x, 0, sizeof(x));
	            memset(y, 0, sizeof(y));
	            if(hungary(i))  break;
	            d = 0x3f3f3f3f;
	            for(j = 0; j < N; j++) {
	                if(x[j]) {
	                    for(k = 0; k < N; k++)
	                        if(!y[k])
	                        d = d < lx[j]+ly[k]-W[j][k] ?
	                            d : lx[j]+ly[k]-W[j][k];
	                }
	            }
	            if(d == 0x3f3f3f3f)  break;
	            for(j = 0; j < N; j++) {
	                if(x[j])    lx[j] -= d;
	                if(y[j])    ly[j] += d;
	            }
	        }
	    }
	    int res = 0;
	    for(i = 0; i < N; i++) {
	        if(my[i] != -1)
	            res += W[my[i]][i];
	    }
	    return res;
	}
} km;

int dist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}
int main() {
	int N, R;
	int x[256], y[256], cost[128][128];
	while (scanf("%d %d", &R, &N) == 2) {
		for (int i = 0; i < R; i++)
			scanf("%d %d", &x[i], &y[i]);
		for (int i = 0; i < N; i++)
			scanf("%d %d", &x[i+R], &y[i+R]);
		
		km.N = R;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < N; j++) {
				cost[i][j] = dist(x[i], y[i], x[j+R], y[j+R]);
				km.W[i][j] = -cost[i][j];
			}
			for (int j = N; j < R; j++)
				km.W[i][j] = 0;
		}
		int ret = km.run();
		printf("%d\n", -ret);
	}
	return 0;
} 
/*
2 2
1 5
2 1
4 2
4 3
3 2
2 1
4 3
7 4
4 5
5 -1
*/ 
 
