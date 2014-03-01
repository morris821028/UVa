//============================================================================
// Name        : paa.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	freopen("pa.in", "r", stdin);
	int N, R;
	int i, j, k, x[101], y[101];
	while(scanf("%d", &N) == 1 && N) {
		scanf("%d", &R);
		for(i = 0; i < N; i++)
			scanf("%d %d", &x[i], &y[i]);
		int Ans = 0;
		for(i = 0; i < N; i++) {
			for(j = i+1; j < N; j++) {
				if((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) > R*R)
					for(k = 0; k < N; k++) {
						if(k == i || k == j)	continue;
						if((x[i]-x[k])*(x[i]-x[k]) + (y[i]-y[k])*(y[i]-y[k]) <= R*R &&
								(x[k]-x[j])*(x[k]-x[j]) + (y[k]-y[j])*(y[k]-y[j]) <= R*R)
							Ans++;
					}
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}
