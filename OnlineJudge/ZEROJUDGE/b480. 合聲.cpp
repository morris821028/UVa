#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
map<string, double> ff;
void merge(const char *s, double A[], int R, int N) {
	int a = 0, b = 0, c = 0;
	double F;	
	for (int i = 0; s[i]; i++) {
		if (isupper(s[i]))		a = s[i];
		else if (isdigit(s[i]))	b = s[i] - '0';
		else if (s[i] == '#')	c = 1;
		else if (s[i] == 'b')	c = -1;
	} 
	double w[] = {0, 2, 3, 5, 7, 8, 10};
	int ww = w[a - 'A'];
	if (a == 'A' || a == 'B')	b++;
	ww += c;
	F = exp(log(220) + (log(440) - log(220)) * ww / 12) * pow(2, b - 4);
	double d = F * 2 * pi / R;
	int ret = 1;
	for (int i = 0; i < N; i++) {
		double f = 32767 * sin(i * d);
		A[i] += f;
	}
}
int main() {
	for (int i = 0; i < 7; i++) {
		double w[] = {0, 2, 3, 5, 7, 8, 10};
		double f = exp(log(220) + (log(440) - log(220)) * w[i] / 12);
		if (i < 2)	f *= 2;
		ff[string(1, i+'A')] = f;
	}
	char s[1024];
	int R = 8000, N = 8000, CNT = 0;
	double A[65536] = {};
	while (scanf("%s", s) == 1)
		merge(s, A, R, N), CNT++;
	printf("%d %d\n", R, N);
	for (int i = 0; i < N; i++) {
		int f = round(A[i] / CNT);
		printf("%d ", f);
	}
	puts("");
	return 0;
}
/*
A1 C5 B#7 G3 Fb2
*/
