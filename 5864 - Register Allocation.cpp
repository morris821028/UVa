#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int st, ed;
}Work;
Work Job[10000];
int cmp(const void *i, const void *j) {
	Work *x, *y;
	x = (Work *)i, y = (Work *)j;
	if(x->st != y->st)
		return x->st - y->st;
    return x->ed - y->ed;
}
int main() {
	int t, n, i, j;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int ans = 0, tn = n;
		for(i = 0; i < n; i++)
			scanf("%d %d", &Job[i].st, &Job[i].ed);
		qsort(Job, n, sizeof(Work), cmp);

		while(tn) {
			int led = -1;
			for(i = 0, j = 0; i < tn; i++) {
				if(led < Job[i].st) {
					led = Job[i].ed;
				} else {
				    Job[j++] = Job[i];
				}
			}
			ans ++;
			tn = j;
		}
		printf("%d\n", ans);
	}
	return 0;
}
