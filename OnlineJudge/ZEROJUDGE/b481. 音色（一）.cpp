#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
void change(const char *s, double A[], int R, int N, double coef[]) {
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
		double x = i * d;
		double f = sin(x);
		f = coef[5]*pow(f, 5) + coef[3]*pow(f, 3) + coef[1]*f;
		A[i] += 32767 * f;
	}
}
int main() {
	char s[1024];
	int R = 8000, N = 8000;
	double A[65536] = {}, coef[6] = {};
	scanf("%s %lf %lf %lf", s, &coef[5], &coef[3], &coef[1]);
	change(s, A, R, N, coef);
	printf("%d %d\n", R, N);
	for (int i = 0; i < N; i++) {
		int f = round(A[i]);
		printf("%d ", f);
	}
	puts("");
	return 0;
}
/*
C#4 1.0 0.0 0.0
*/
