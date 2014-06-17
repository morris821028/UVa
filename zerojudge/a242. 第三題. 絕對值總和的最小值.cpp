#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int ai, xi, ti;
}f_of_x;
f_of_x D[100000];
int cmp(const void *a, const void *b) {
	f_of_x *i, *j;
	i = (f_of_x *)a, j = (f_of_x *)b;
	if(i->ti != j->ti)
		return i->ti - j->ti;
	return i->ai - j->ai;
}
int f(int x, int n) {
	int i, sum = 0;
	for(i = 0; i < n; i++)
		sum += D[i].ai * abs(x - D[i].ti);
	return sum;
}
int main() {
	int m, n, i;
	scanf("%d", &m);
	while(m--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%d %d", &D[i].ai, &D[i].xi);
			D[i].ti = D[i].xi/D[i].ai;
		}
		qsort(D, n, sizeof(f_of_x), cmp);
		int sum_ai = 0, right_ai = 0, left_ai = 0;
		for(i = 0; i < n; i++)
			sum_ai += D[i].ai;
		for(i = 0; i < n; i++) {
			left_ai += D[i].ai;
			right_ai = sum_ai - left_ai;
			if(left_ai - right_ai >= 0)
				break;
		}
		int min_ti = D[i].ti;
		printf("%d\n", f(min_ti, n));
	}
	return 0;
}
/*
 |a1x - x1| + |a2x - x2| + ... + |anx - xn| ……
=>a1|x - t1| + a2|x - t2| + ... + an|x - tn| ……
=> sort t1 < t2 < t3 ...
=> f'(i) = a1 + a2 + ... + ai - a(i+1) - ... - an
=> 當 x = t? 時的微分 
*/
