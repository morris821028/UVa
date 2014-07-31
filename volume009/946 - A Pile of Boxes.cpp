#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int inner[105], outer[105], footer[105];
int height[105], A[105];

int place(int i, int mxI, int limit) {
//	printf("down %d %d\n", A[mxI], mxI);
	if(A[mxI] < A[i]) {
		if(height[mxI] + A[i] <= limit) {
			outer[mxI] = i, footer[i] = mxI; 
			height[i] = height[mxI] + A[i];
		}
		return height[mxI] + A[i];
	}
	if(inner[mxI] == -1) {
		int h = place(i, footer[mxI], height[mxI] - A[mxI]);
		if(h <= height[mxI] - A[mxI]) // complete
			return h;
		inner[mxI] = i, footer[i] = footer[mxI];
		height[i] = height[mxI] - A[mxI] + A[i];
		return height[i];
	} else {
		mxI = inner[mxI];
		while(outer[mxI] != -1)
			mxI = outer[mxI];
		int h = place(i, mxI, height[mxI]);
		if(h == height[mxI] - A[mxI] + A[i]) {
			h = place(i, footer[mxI], height[mxI] - A[mxI]);
//			printf("check %d %d\n", h, height[mxI] - A[mxI]);
			if(h <= height[mxI] - A[mxI])
				return h;
			inner[mxI] = i, footer[i] = footer[mxI];
			height[i] = height[mxI] - A[mxI] + A[i];
			return height[i];
		} else if(h > height[mxI]) {
			if(height[mxI] + A[i] <= limit) {
				outer[mxI] = i, footer[i] = mxI;
				height[i] = height[mxI] + A[i];
			}
			return height[mxI] + A[i];
		} else {
//			puts("hello");
			return h;
		}
	}
}
int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		for(int i = 0; i <= n; i++)
			inner[i] = outer[i] = footer[i] = height[i] = -1;
		A[0] = 0, height[0] = 0;
		for(int i = 1; i <= n; i++)
			scanf("%d", &A[i]);
		int mxH = 0, mxI = 0;
		for(int i = 1; i <= n; i++) {
			int h = place(i, mxI, mxH);
			if(h > mxH) {
				outer[mxI] = i, footer[i] = mxI; 
				height[i] = height[mxI] + A[i];
			}
			h = height[i];
//			printf("[%d] %d - %d mxH = %d mxI %d\n", i, A[i], h, mxH, mxI);
//			for(int j = 1; j <= i; j++)
//				printf("--------[%d] %2d * in %2d out %2d foot %2d\n", j, A[j], inner[j], outer[j], footer[j]);
			if(h > mxH)	mxH = h, mxI = i;
		}
		printf("%d\n", mxH);
	}
	return 0;
}
/*
8
10
4
6
3
11
7
8
5
*/
