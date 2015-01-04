#include <stdio.h>
#include <algorithm>
using namespace std;

#define MAXN 128
int read(char exp[]) {
	char c, *p = exp;
	while (c = getchar()) {
		if (c == EOF)	return 0;
		if (c != ' ' && c != '\n')
		*p = c, p++;
		if (c == ';')	break;
	}
	*p = '\0';
	return 1;
}
char exp[32767], *ptr;
void merge(int xw, int xh, char X[][MAXN], 
			int yw, int yh, char Y[][MAXN], 
			int &w, int &h, char ret[][MAXN]) {
	for (int i = 0; i < xw; i ++)
		for (int j = 0; j < xh; j++)
			ret[i][j] = X[i][j];
	for (int i = 0; i < yw; i ++)
		for (int j = 0; j < yh; j++)
			ret[i][j + xh] = Y[i][j];
	w = xw, h = xh + yh;
}
char trans(char c) {
	if (c == '-')	return '|';
	if (c == '|')	return '-';
	if (c == '+')	return '+';
	if (c == '/')	return '\\';
	if (c == '\\')	return '/';
	return '.';
}
void rotate90(int xw, int xh, char X[][MAXN], 
			int &w, int &h, char ret[][MAXN]) {
	for (int i = 0; i < xw; i++) {
		for (int j = 0; j < xh; j++) {
			ret[j][xw - i - 1] = trans(X[i][j]);
		}
	}
	w = xh, h = xw;
}
int parsing(int &w, int &h, char ret[][MAXN]) {
	if (*ptr == 'A') {
		w = 2, h = 2;
		ret[0][0] = '/', ret[0][1] = '/';
		ret[1][0] = '/', ret[1][1] = '+';
		ptr++;
		return 1;
	}
	if (*ptr == 'B') {
		w = 2, h = 2;
		ret[0][0] = '-', ret[0][1] = '-';
		ret[1][0] = '-', ret[1][1] = '-';
		ptr++;
		return 1;
	}
	if (*ptr == 's' && *(ptr+1) == 'e' && *(ptr+2) == 'w') {
		ptr += 4; // 'sew('
		char X[MAXN][MAXN], Y[MAXN][MAXN];
		int xw, xh, yw, yh, f = 1;
		f &= parsing(xw, xh, X);
		ptr++; // ','
		f &= parsing(yw, yh, Y);
		ptr++; // ')'
		f &= xw == yw;
		if (f)
			merge(xw, xh, X, yw, yh, Y, w, h, ret);
		return f;
	}
	if (*ptr == 't' && *(ptr+1) == 'u' && *(ptr+2) == 'r' && *(ptr+3) == 'n') {
		ptr += 5; // 'turn('
		char X[MAXN][MAXN];
		int xw, xh, f = 1;
		f &= parsing(xw, xh, X);
		if (f)
			rotate90(xw, xh, X, w, h, ret); 
		ptr++;
		return f;
	}
}
int main() {
	int cases = 0;
	while (read(exp)) {
		printf("Quilt %d:\n", ++cases);
		ptr = exp;
		int w, h;
		char ret[MAXN][MAXN];
		int f = parsing(w, h, ret);
		if (!f)	puts("error");
		else {
			for (int i = 0; i < w; i++, puts("")) {
				for (int j = 0; j < h; j++)
					printf("%c", ret[i][j]);
			}
		}
	}
	return 0;
}
/*
sew(turn(sew(B,turn(B))), 
       turn(sew(turn(B),B)))   ; 
   
   
   sew(turn(sew(B,turn(B))),A); 
sew(turn(sew(A,turn(A))), 
 turn(turn(
   
   turn(sew(A,turn(A))))))
   
   ;
*/
