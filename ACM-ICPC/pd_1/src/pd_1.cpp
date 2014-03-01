//============================================================================
// Name        : pd_1.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#define oo 10000000
using namespace std;
typedef struct {
	int st, ed;
}Work;
Work Job[10000];
int cmp(const void *i, const void *j) {
	Work *x, *y;
	x = (Work *)i, y = (Work *)j;
	if(x->st != y->st)
		return x->st - y->st;
	else
		return x->ed - y->ed;
}
int main() {
	//freopen("pd.in", "r", stdin);
	int t, n, i;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int Ans = 0, tn = n, Used[10000];
		for(i = 0; i < n; i++)
			scanf("%d %d", &Job[i].st, &Job[i].ed), Used[i] = 0;
		qsort(Job, n, sizeof(Work), cmp);

		while(tn) {
			int led = -1;
			for(i = 0; i < n; i++) {
				if(Used[i] == 0 && led < Job[i].st) {
					Used[i] = 1;
					led = Job[i].ed;
					tn--;
				}
			}
			Ans ++;
		}
		printf("%d\n", Ans);
	}
	return 0;
}
