#include <stdio.h>
#include <stdlib.h>
typedef struct Element {
	int sum, x, y;
};
int cmp1(const void *i, const void *j) {
	return *(int *)i - *(int *)j;
}
int cmp2(const void *i, const void *j) {
	Element *a, *b;
	a = (Element *)i, b = (Element *)j;
	return a->sum - b->sum;
}
Element sub[1000000];
int search(int v, int a, int b, int n) {
	int l, r, m, i;
	l = 0, r = n;
	while(l <= r) {
		m = (l+r)/2;
		if(sub[m].sum > v)
			r = m-1;
		else if(sub[m].sum < v)
			l = m+1;
		else {
			for(i = m; i <= r; i++) {
				if(sub[i].sum != v)	
					break;
				if(a != sub[i].x && a != sub[i].y 
					&& b != sub[i].x && b != sub[i].y)
					return 1;
			}
			
			for(i = m-1; i >= l; i--) {
				if(sub[i].sum != v)	
					break;
				if(a != sub[i].x && a != sub[i].y 
					&& b != sub[i].x && b != sub[i].y)
					return 1;
			}
			return 0;
		}
	}
	return 0;
}
int main() {
	int n, S[1000], i, j;
	while(scanf("%d", &n) == 1 && n) {
		for(i = 0; i < n; i++)
			scanf("%d", &S[i]);
		qsort(S, n, sizeof(int), cmp1);
		int m = 0;
		for(i = 0; i < n; i++) {
			for(j = i+1; j < n; j++) {
				sub[m].sum = S[i]+S[j];
				sub[m].x = S[i];
				sub[m].y = S[j];
				m++;
			}
		}
		qsort(sub, m, sizeof(Element), cmp2);
		int flag = 0, max = -536870912*2, test;
		for(i = n-1; i >= 0; i--) {
			if(flag)	break;
			for(j = 0; j < n; j++) {
				if(flag)	break;
				if(i == j)	continue;
				test = search(S[i]-S[j], S[i], S[j], m-1);
				if(test == 1) {
					max = S[i], flag = 1;
				}
			}
		}
		if(flag == 0)
			puts("no solution");
		else
			printf("%d\n", max);
	}
    return 0;
}
