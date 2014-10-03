#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <algorithm>
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
	int cases = 0;
    int n, x[105], y[105];
    while(scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++) {
        	scanf("%d %d", &x[i], &y[i]);
        	x[i]--, y[i]--;
        }
        km.N = n;
        int ret = -0x3f3f3f3f;
        for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++)
        		for (int k = 0; k < n; k++)
        			km.W[j][k] = -dist(x[j], y[j], i, k);
        	ret = max(ret, km.run());
        }
        for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++)
        		for (int k = 0; k < n; k++)
        			km.W[j][k] = -dist(x[j], y[j], k, i);
        	ret = max(ret, km.run());
    	}
    	for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++)
        		km.W[j][i] = -dist(x[j], y[j], i, i);	
    	}
		ret = max(ret, km.run());
    	for (int i = 0; i < n; i++) {
        	for (int j = 0; j < n; j++)
        		km.W[j][i] = -dist(x[j], y[j], i, n - i - 1);
    	}
		ret = max(ret, km.run());
        printf("Board %d: %d moves required.\n\n", ++cases, -ret);
    }
    return 0;
}
