#include<stdio.h>
typedef struct {
	char s[2];
	double x1, x2, x3, y1, y2, y3;
	double r;
}D;
D Data[100];
int rectangle(double x, double y, int idx, int in) {
	if(Data[idx].x1 <= x && Data[idx].x2 >= x && Data[idx].y1 >= y && Data[idx].y2 <= y) {
		printf("Point %d is contained in figure %d\n", in, idx+1);
		return 1;
	}
	return 0;
}
double Determinant(double x1, double y1, double x2, double y2, double x3, double y3) {
	return (x1*y2+x2*y3+x3*y1) - (x2*y1+x3*y2+x1*y3);
}
int triangle(double x, double y, int idx, int in) {
	if(Determinant(Data[idx].x1, Data[idx].y1, Data[idx].x2, Data[idx].y2, x, y) * 
	Determinant(Data[idx].x1, Data[idx].y1, Data[idx].x2, Data[idx].y2, Data[idx].x3, Data[idx].y3) < 0)
		return 0;
	if(Determinant(Data[idx].x1, Data[idx].y1, Data[idx].x3, Data[idx].y3, x, y) * 
	Determinant(Data[idx].x1, Data[idx].y1, Data[idx].x3, Data[idx].y3, Data[idx].x2, Data[idx].y2) < 0)
		return 0;
	if(Determinant(Data[idx].x2, Data[idx].y2, Data[idx].x3, Data[idx].y3, x, y) * 
	Determinant(Data[idx].x2, Data[idx].y2, Data[idx].x3, Data[idx].y3, Data[idx].x1, Data[idx].y1) < 0)
		return 0;	
	printf("Point %d is contained in figure %d\n", in, idx+1);
	return 1;
}
int circle(double x, double y, int idx, int in) {
	if((Data[idx].x1-x)*(Data[idx].x1-x) + (Data[idx].y1-y)*(Data[idx].y1-y) <= Data[idx].r * Data[idx].r) {
		printf("Point %d is contained in figure %d\n", in, idx+1);
		return 1;
	}
	return 0;
}
void Judge(double x, double y, int n, int test) {
	int i, sum = 0;
	for(i = 0; i < n; i++) {
		switch(Data[i].s[0]) {
			case 'r':sum += rectangle(x, y, i, test);break;
			case 't':sum += triangle(x, y, i, test);break;
			case 'c':sum += circle(x, y, i, test);break;
		}
	}
	if(!sum)
		printf("Point %d is not contained in any figure\n", test);
} 
int main() {
	char s[2];
	int in = 0, test = 1;
	double x, y;
	while(scanf("%s", s) == 1 && s[0] != '*') {
		Data[in].s[0] = s[0];
		if(s[0] == 'r')
			scanf("%lf %lf %lf %lf", &Data[in].x1, &Data[in].y1, &Data[in].x2, &Data[in].y2);
		else if(s[0] == 't')
			scanf("%lf %lf %lf %lf %lf %lf", &Data[in].x1, &Data[in].y1, &Data[in].x2, &Data[in].y2, &Data[in].x3, &Data[in].y3);
		else
			scanf("%lf %lf %lf", &Data[in].x1, &Data[in].y1, &Data[in].r);
		in++;
	}
	while(scanf("%lf %lf", &x, &y) == 2, !(x == 9999.9 && y == 9999.9)) {
		Judge(x, y, in, test), test++;
	}
	return 0;
}
