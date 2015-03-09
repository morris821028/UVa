
#include<stdio.h>
struct coordinate {
	double x, y, w, l;
}A[100001];
double x, y, r;
double tw, tl, rx, lx, uy, dy;
int T, n, a;
int judgein(double x, double y, double rx, double ry, double r) {
	if((rx-x)*(rx-x) + (ry-y)*(ry-y) <= r*r) return 1;
	return 0; 
} 
double point() {
	char cha;
	double poi = 0, num = 1;
    while(cha = getchar())	{  
    	if(cha == ' ' || cha == '\n') break;  
		num=num/10;
		poi=poi + (cha-48)*num;
	}  
	return poi;
}        
double Input() {
    char cha,flag = 1;  
    double x = 0;  
	while(cha = getchar())  
    	if(cha != ' ' && cha != '\n') break;  
    if(cha != '-') x = x*10 + cha-48;
    else flag = -1;
    while(cha = getchar()) {  
		if(cha == ' ' || cha == '\n') break;  
		if(cha == '.') {
        	x = x + point();
            break;
        }
        x = x*10 + cha-48;
	}  
    return x*flag;
}
main() {

	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(a = 0; a < n; a++) { 
			A[a].x = Input(), A[a].y = Input(), A[a].w = Input(), A[a].l = Input(); 
		} 
		scanf("%lf %lf %lf", &x, &y, &r);
		int Ans = 0;
		for(a = 0; a < n; a++) {

			if(A[a].x + A[a].w/2 >= x - r && A[a].x - A[a].w/2 <= x + r 
			&& A[a].y + A[a].l/2 >= y && A[a].y - A[a].l/2 <= y) Ans++;
			else if(A[a].x + A[a].w/2 >= x && A[a].x - A[a].w/2 <= x 
			&& A[a].y + A[a].l/2 + r >= y && A[a].y - A[a].l/2 - r <= y)  Ans++;
			else {			
				tw = A[a].w /2.0, tl = A[a].l /2.0;
				rx = A[a].x + tw, lx = A[a].x - tw;
				uy = A[a].y + tl, dy = A[a].y - tl;
				if(judgein(rx, uy, x, y, r)) Ans++; 
				else if(judgein(rx, dy, x, y, r)) Ans++;  
				else if(judgein(lx, uy, x, y, r)) Ans++; 
				else if(judgein(lx, dy, x, y, r)) Ans++; 
			} 
		}
		printf("%d\n", Ans);
	}
	return 0;
}
