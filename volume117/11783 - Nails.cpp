#include <stdio.h>
#include <math.h> 
#include <algorithm>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;

struct Pt {
    int x, y;
    Pt(int a=0, int b=0) :
    	x(a), y(b) {}
};
#define eps 1e-8
long long cross(Pt o, Pt a, Pt b) {
    return (long long)(a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs)*cross(as, at, bt) <= 0 &&
       cross(at, as, bs)*cross(at, as, bt) <= 0 &&
       cross(bs, bt, as)*cross(bs, bt, at) <= 0 &&
       cross(bt, bs, as)*cross(bt, bs, at) <= 0)
        return 1;
    return 0;
}

int main() {
	int n;
	Pt Ds[1024], De[1024];
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 0; i < n; i++)
			scanf("%d %d %d %d", &Ds[i].x, &Ds[i].y, &De[i].x, &De[i].y);
		
		int used[1024] = {};
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				if(intersection(Ds[i], De[i], Ds[j], De[j]))
					used[i]++, used[j]++;
			}
		}
		
		int ret = 0;
		for(int i = 0; i < n; i++)
			ret += used[i] ? used[i] : 4;
		printf("%d\n", ret /2);
	}
	return 0;
}
