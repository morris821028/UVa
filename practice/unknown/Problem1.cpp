#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxV 100000000
typedef struct {
    double x, y;
}Point;
typedef struct {
    Point s, e;
}Segment;
double Min(double x, double y) {
    return x < y ? x : y;
}
double Max(double x, double y) {
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
    double miny = x.y, maxy = x.y;
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

main() {
    int n, i, j, k, x, y, TT;
    Point T;
    scanf("%d", &TT);
    while(TT--) {
		Point PP[6];
        for(i = 0; i < 6; i++) {
			scanf("%lf %lf", &PP[i].x, &PP[i].y);
        }
        Segment A[3], B[3];
        for(i = 0, k = 0; i < 3; i++)
        	for(j = i+1; j < 3; j++) {
				A[k].s.x = PP[i].x, A[k].s.y = PP[i].y, A[k].e.x = PP[j].x, A[k].e.y = PP[j].y;
	            if(A[k].s.x > A[k].e.x) {
    	            T = A[k].s, A[k].s = A[k].e, A[k].e = T;
				}
				k++;
            }
		
        for(i = 3, k = 0; i < 6; i++)
        	for(j = i+1; j < 6; j++) {
				B[k].s.x = PP[i].x, B[k].s.y = PP[i].y, B[k].e.x = PP[j].x, B[k].e.y = PP[j].y;
	            if(B[k].s.x > B[k].e.x) {
    	            T = B[k].s, B[k].s = B[k].e, B[k].e = T;
				}
				k++;
            }
        int flag = 0;
        for(i = 0; i < 3; i++)
        	for(j = 0; j < 3; j++)
        		if(JudgeIntersect(A[i], B[j]))
        			flag = 1;
        /*if(flag)
        	printf("Not Disjoint\n");
        else
        	printf("Disjoint\n");*/
        int tflag = 0;
        for(j = 3; j < 6; j++) {
			tflag = 0;
        	for(i = 0; i < 3; i++) {
				if(!Cross(A[i].s, PP[j], PP[2-i], A[i].e)) {
					tflag ++;
				}
			}
			if(tflag == 3)
				flag = 1;
		}
        for(j = 0; j < 3; j++) {
			tflag = 0;
        	for(i = 0; i < 3; i++) {
				if(!Cross(B[i].s, PP[j], PP[5-i], B[i].e)) {
					tflag ++;
				}
			}
			if(tflag == 3)
				flag = 1;
		}
        if(flag)
        	printf("Not Disjoint\n");
        else
        	printf("Disjoint\n");
    }
    return 0;
} /*
3
0.0 0.0 1.0 0.0 0.0 2.0
0.0 0.0 -1.0 0.0 -1.0 -1.0
0.0 0.0 1.0 0.0 0.0 2.0
-0.5 -0.5 -1.0 0.0 -1.0 -1.0
0.1 0.1 0.1 0.2 0.5 0.5
0.0 0.0 1.0 0.0 0.0 2.0

*/
