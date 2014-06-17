#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
char s[2122][2000];
int k = 0, st;
void simpleRecFunc(int a, int b, int *v) {
	s[k][st++] = 1, s[k][st++] = 2;
	//printf("1 2 ");
	if(a <= 2) {
		//printf("3 ");
		s[k][st++] = 3;
		*v = b+1;
	} else {
		//printf("4 5 ");
		s[k][st++] = 4, s[k][st++] = 5;
		if(a > b) {
			//printf("6 ");
			s[k][st++] = 6;
			*v = *v + 1;
		}
		else {
			//printf("7 8 ");
			s[k][st++] = 7, s[k][st++] = 8;
			*v = *v - 1;
		}
		//printf("9 ");
		s[k][st++] = 9;
		if(a < b + 1) {
			//printf("10 ");
			s[k][st++] = 10;
			simpleRecFunc(a-1, b, v);
			//printf("11 ");
			s[k][st++] = 11;
			simpleRecFunc(a-2, *v, v);
		} else {
			//printf("12 13");
			s[k][st++] = 12, s[k][st++] = 13;
			simpleRecFunc(a-3, *v, v);
			s[k][st++] = 14;
			//printf("14 ");
		}

	}
	s[k][st++] = 15;
	//printf("15 ");
}
void Build() {
	//printf("16 17 18 19 20 ");
	int i, j;
	for(i = 0; i <= 20; i++)
		for(j = 0; j <= 100; j++) {
			s[k][0] = 16, s[k][1] = 17, s[k][2] = 18, s[k][3] = 19, s[k][4] = 20;
			st = 5;
			int x = i, y = j, z = 0;
			simpleRecFunc(x, y, &z);
			//printf("21\n");
			s[k][st++] = 21;
			s[k][st++] = -1;
			k++;
		}
}
int main() {
	Build();
	int T;
	char Sa[100000];
	scanf("%d", &T);
	gets(Sa);
	while(T--) {
		gets(Sa);
		int A[1025], n = 0, tmp = 0, g = 0, i, j;
		for(i = 0; Sa[i]; i++)
			if(Sa[i] >= '0' && Sa[i] <= '9')
				g = 1, tmp = tmp * 10+ Sa[i]-'0';
			else {
				if(g) {
					A[n++] = tmp;
				}
				tmp = 0, g = 0;
			}
		if(g) {
			A[n++] = tmp;
		}
		A[n++] = -1;
		int flag = 0;
		for(i = 0; i < k; i++) {
			for(j = 0; s[i][j] != -1; j++)
				if(s[i][j] != A[j])
					break;
			if(s[i][j] == -1 && A[j] == -1) {
				flag = 1;
				break;
			}
		}
		puts(flag ? "feasible" : "infeasible");
	}
	return 0;
}
