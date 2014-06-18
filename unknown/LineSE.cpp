#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxV 1000000
typedef struct {
	int x, y;
}Point;
typedef struct {
	Point s, e;
}Segment;
Segment D[14];
int Map[14][14];
int Min(int x, int y) {
	return x < y ? x : y;
}
int Max(int x, int y) {
	return x > y ? x : y;
}
int Cross(Point s, Point t1, Point t2, Point e) {
	Point T1, T2, M;
	M.x = e.x-s.x, M.y = e.y-s.y;
	T1.x = t1.x-s.x, T1.y = t1.y-s.y;
	T2.x = t2.x-s.x, T2.y = t2.y-s.y;
	return (M.x*T1.y - M.y*T1.x)*(M.x*T2.y - M.y*T2.x) < 0 ? 1 : 0;
}
int Collinear(Point x, Point y, Point z) {/*x-y-z (O) y-x-Z(X)*/
	int miny = x.y, maxy = x.y;
	miny = Min(x.y, z.y);
	maxy = Max(x.y, z.y);
	if((x.x-y.x)*(z.y-y.y) == (x.y-y.y)*(z.x-y.x) && (x.x <= y.x && z.x >= y.x) && 
		(miny <= y.y && maxy >= y.y))
		return 1;
	return 0;
} 
int JudgeIntersect(Segment A, Segment B) {
	if(Cross(A.s, B.s, B.e, A.e) && Cross(A.e, B.s, B.e, A.s) &&
		Cross(B.s, A.s, A.e, B.e) && Cross(B.e, A.s, A.e, B.s))
		return 1;
	if(Collinear(A.s, B.s, A.e) || Collinear(A.s, B.e, A.e) ||
		Collinear(B.s, A.s, B.e) || Collinear(B.s, A.e, B.e) )
		return 1;
	return 0;
}
void Handle(int n) {
	int i, j;
	memset(Map, 0, sizeof(Map));
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if(JudgeIntersect(D[i], D[j]))
				Map[i][j] = 1;
		}
	}
}
void Floyd(int n) {
	int i, j, k;
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			if(Map[i][j] == 0)
				Map[i][j] = MaxV;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			for(k = 0; k < n; k++)
				if(Map[j][i] + Map[i][k] < Map[j][k])
					Map[j][k] = Map[j][i] + Map[i][k];
}
main() {
	int n, i, j, k, x, y;
	Point T;
	scanf("%d", &k);
	while(k--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%d %d %d %d", &D[i].s.x, &D[i].s.y, &D[i].e.x, &D[i].e.y);
			if(D[i].s.x > D[i].e.x) {
				T = D[i].s, D[i].s = D[i].e, D[i].e = T;
			}
		}
		Handle(n), Floyd(n);
		while(scanf("%d %d", &x, &y) == 2) {
			if(x == 0 && y == 0)	break;
			x--, y--;
			if(Map[x][y] == MaxV)
				puts("NOT CONNECTED");
			else
				puts("CONNECTED");
		}
		puts("");
	}
	return 0;
}
