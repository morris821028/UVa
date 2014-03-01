#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define oo 0xffffff
typedef struct {
	int x, y;
}Path;
Path data[1000000];
int cmp(const void *i, const void *j) {
	Path *x, *y;
	x = (Path *)i, y = (Path *)j;
	return x->x - y->x;
}
int min(int x, int y) {
	return x < y ? x : y;
}
int NodeT[5001], NodeL[5001];
int Ans[5001], At, Used[5001], Time[5001];
int BFS(int n, int st) {
	int i, j, k;
	int Ans2[5001], At2 = 0;
	int Q[5001], Used[5001] = {0}, Qt, Dis[5001] = {0};
	Dis[st] = 1;
	for(i = 0;  i <= Qt; i++) {
		int tn = Q[i];
		for(j = 0, k = NodeL[tn]; j < NodeT[tn]; j++, k++) {
			if(Used[data[k].y] == 0) {
				Used[data[k].y] = 1;
				Qt++;
				Q[Qt] = data[k].y;
				Dis[Q[Qt]] = Dis[tn]+1;
				if(Ans[Q[Qt]] == 1)	Ans2[At2++] = Q[Qt];
			}
		}
	}
	for(i = 0; i < At2-1; i++)
		printf("%d ", Ans2[i]);
	printf("%d\n", Ans2[i]);
}
int DFS(int T, int now, int start, int *p) {
    int last = oo, i, j, tmp, flag = 0, ttry = 0;
    Time[now] = T;
    int findmain = 0;
    for(i = 0, j = NodeL[now]; i < NodeT[now]; i++, j++) {
        if(Used[data[j].y] == 0) {
            Used[data[j].y] = 1;
            tmp = DFS(T+1, data[j].y, 0, &findmain);
            if(tmp >= T)    flag = 1;
            last = tmp < last ? tmp : last;
            ttry++;
        } else {
            tmp = Time[data[j].y];
            last = tmp < last ? tmp : last;
        }
    }
    if(start != 1 && findmain == 1) {
		if(flag)
			Ans[now] = 1;
    }
    if(now == 0 || findmain == 1)	*p = 1;
    return last;
}
int main() {
	int n, m, k;
	while(scanf("%d %d %d", &n, &m, &k) == 3) {
		if(n == 0 &&  m == 0 && k == 0)	break;
		int i, j;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &data[i].x, &data[i].y);
			data[m+i].x = data[i].y;
			data[m+i].y = data[i].x;
		}
		for(i = 0; i < n; i++) {
			NodeL[i] = oo;
			Time[i] = 0, Used[i] = 0;
		}
		qsort(data, 2*m, sizeof(Path), cmp);
		for(i = 0; i < 2*m; i++) {
			NodeT[data[i].x]++;	
			NodeL[data[i].x] = min(NodeL[data[i].x], i);
		}
		int st;
		while(k--) {
			scanf("%d", &st);
			memset(Used, 0, sizeof(Used));
			memset(Time, 0, sizeof(Time));
			memset(Ans, 0, sizeof(Ans));
			At = 0;
			Used[st] = 1, Time[st] = 1;
			DFS(1, st, 1, &i);
			if(At == 0)	puts("NOFEASLIBLE");
			else {
				BFS(n,  st);
			}
		}
	}
    return 0;
}
/*
5 4 4
0 1
1 2
2 3
3 4
4
3
2
1
5 5 1
0 1
0 2
1 3
2 3
3 4
4
0 0 0
*/
