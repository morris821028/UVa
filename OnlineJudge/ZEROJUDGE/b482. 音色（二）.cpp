#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
void change(const char *s, double A[], int R, int N, pair<double, double> coef[], int P) {
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
		double f = sin(i * d);
		double x = i * d / (F * 2 * pi), y = 0;
		for (int j = P-1; j >= 0; j--) {
			if (coef[j].first <= x) {
				double x1, x2, y1, y2;
				x1 = coef[j].first, y1 = coef[j].second;
				if (j+1 < P) {
					x2 = coef[j+1].first, y2 = coef[j+1].second;
					y = y1 + (y2 - y1) * (x - x1) / (x2 - x1);
				} else {
					x2 = x1, y2 = y1;
					y = y1;
				}
				break;
			}
		}
		A[i] += 32767 * f * y;
	}
}
int main() {
	char s[1024];
	int R = 8000, N = 8000, P;
	double A[65536] = {};
	pair<double, double> coef[16];
	scanf("%s", s);
	scanf("%d", &P);
	for (int i = 0; i < P; i++)
		scanf("%lf %lf", &coef[i].first, &coef[i].second);
	sort(coef, coef + P);
	change(s, A, R, N, coef, P);
	printf("%d %d\n", R, N);
	for (int i = 0; i < N; i++) {
		int f = round(A[i]);
		printf("%d ", f);
	}
	puts("");
	return 0;
}
/*
C#4
3 0.0 0.0 0.2 1.0 1.0 0.0
*/
