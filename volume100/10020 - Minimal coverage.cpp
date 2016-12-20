#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int x, y;
}Seg;
int cmp(const void *i, const void *j) {
	Seg *a, *b;
	a = (Seg *)i, b = (Seg *)j;
	if(a->x != b->x)
		return a->x - b->x;
	return a->y - b->y;
}
int main() {
	int T, M, N, x, y;
	Seg Data[100000];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &M);
		N = 0;
		while(scanf("%d %d", &x, &y) == 2) {
			if(x == 0 && y == 0)	break;
			Data[N].x = x;
			Data[N].y = y;
			N++;
		}
		qsort(Data, N, sizeof(Seg), cmp);
		Seg Ans[100000];
		int CoverR = 0, NextCoverR = 0, i = 0, Aidx = 0, tmp;
		while(i < N) {
			CoverR = NextCoverR;
			tmp = -1;
			while(i < N && Data[i].x <= CoverR) {
				if(Data[i].y > NextCoverR) {
					NextCoverR = Data[i].y;
					tmp = i;
				}
				i++;
			}
			if(tmp < 0)	{
				if(CoverR < M)	Aidx = 0;
				break;
			}
			Ans[Aidx++] = Data[tmp];
			if(NextCoverR >= M)	break;
			i = tmp+1;
		}
		if(Aidx == 0)	puts("0");
		else {
			printf("%d\n", Aidx);
			for(i = 0; i < Aidx; i++)
				printf("%d %d\n", Ans[i].x, Ans[i].y);
		}
		if(T)	puts("");
	}
    return 0;
}

