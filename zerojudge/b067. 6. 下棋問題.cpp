#include<stdio.h>
#include<string.h>
#define oo 2147483647
unsigned int link[1290000];
struct {
	int x, y, num;
}Point[5001];
int First[5001], Second[5001], Third[5001], Fourth[5001];
void modifybit(int state) {
	static int i, j;
	i = state>>5, j = state&31;
	link[i] ^= (1<<j);
}
int findbit(int state) {
	static int i, j;
	i = state>>5, j = state&31;
	return link[i]&(1<<j);
}
int Calu(int x, int y, int n, int idx) {
	int Fy = oo, Sy = oo, Ty = -oo, Fthy = -oo;
	int i, j, Ft, St, Tt, Ftht;
	Ft = St = Tt = Ftht = 0;
	for(i = idx+1; i <= n; i++) {
		if(Point[i].y > y) {
			if(Point[i].y < Fy) {
				Fy = Point[i].y;
				First[Ft++] = Point[i].num;
			}
		} else {
			if(Point[i].y > Fthy) {
				Fthy = Point[i].y;
				Fourth[Ftht++] = Point[i].num;
			}
		}
	}
	for(i = idx-1; i >= 0; i--) {
		if(Point[i].y > y) {
			if(Point[i].y < Sy) {
				Sy = Point[i].y;
				Second[St++] = Point[i].num;
			}
		} else {
			if(Point[i].y > Ty) {
				Ty = Point[i].y;
				Third[Tt++] = Point[i].num;
			}
		}
	}
	int nodex = Point[idx].num, nodey;
	int Ans = Ft + St + Tt + Ftht;
	for(i = 0; i < Ft; i++) {
		nodey = First[i];
		modifybit((nodey<<13)|nodex);
	}
	for(i = 0; i < St; i++) {
		nodey = Second[i];
		modifybit((nodey<<13)|nodex);
	}
	for(i = 0; i < Tt; i++) {
		nodey = Third[i];
		modifybit((nodex<<13)|nodey);
	}
	for(i = 0; i < Ftht; i++) {
		nodey = Fourth[i];
		modifybit((nodex<<13)|nodey);
	}
	for(i = 0; i < Ft; i++) {
		for(j = 0; j < Tt; j++) {
			nodex = First[i], nodey = Third[j];
			if(findbit((nodex<<13)|nodey))
				Ans--, modifybit((nodex<<13)|nodey);
		}
	}
	for(i = 0; i < St; i++) {
		for(j = 0; j < Ftht; j++) {
			nodex = Second[i], nodey = Fourth[j];
			if(findbit((nodex<<13)|nodey))
				Ans--, modifybit((nodex<<13)|nodey);
		}
	}
	return Ans;
}
main() {
	int n, i, j, x, y;
	while(scanf("%d", &n) == 1) {
		memset(link, 0, sizeof(link));
		long long A = 0, B = 0, Score = 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			for(j = i-1; j >= 0; j--)
				if(Point[j].x > x)	Point[j+1] = Point[j];
				else	break;
			Point[j+1].x = x, Point[j+1].y = y, Point[j+1].num = i;
			Score += Calu(x, y, i, j+1);
			if(i&1)	B += Score;
			else	A += Score;
		}
		printf("%lld %lld\n", A, B);
	}
	return 0;
}
/*
4
2 3
3 4
1 2
4 1
7
1 5
2 7
3 8
5 1
6 2
7 3
4 4
*/
