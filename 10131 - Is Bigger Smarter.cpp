#include <stdio.h>
#include <stdlib.h>
typedef struct Data {
	int W, S, node;
};
Data ele[1000];
int cmp(const void *i, const void *j) {
	Data *a, *b;
	a = (Data *)i, b = (Data *)j;
	if(a->W != b->W)
		return a->W - b->W;
	return a->S - b->S;
}
void LDS(int n) {
	int i, j;
	int DP[1000] = {}, source[1000] = {};
	for(i = 0; i < n; i++)
		DP[i] = 1, source[i] = i;
	for(i = 0; i < n; i++) {
		for(j = i-1; j >= 0; j--) {
			if(ele[i].W != ele[j].W && ele[i].S < ele[j].S) {
				if(DP[i] <= DP[j]+1) {
					DP[i] = DP[j]+1;
					source[i] = j;
				}
			}
		}
	}
	int max = 0, start;
	for(i = 0; i < n; i++)
		if(DP[i] > max)
			max = DP[i], start = i;
	printf("%d\n", max);
	int Ans[1000], idx = 0;
	while(source[start] != start) {
		Ans[idx++] = ele[start].node+1;
		start = source[start];
	}
	Ans[idx++] = ele[start].node+1;
	for(i = max-1; i >= 0; i--)
		printf("%d\n", Ans[i]);
}
int main() {
	int n = 0;
	while(scanf("%d %d", &ele[n].W, &ele[n].S) == 2)
		ele[n].node = n, n++;
	qsort(ele, n, sizeof(Data), cmp);
	LDS(n);
    return 0;
}
