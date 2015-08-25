#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
void make(const char *s, double A[], int R, int N) {
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
		A[i] = round(32767 * f);
	}
}
double test(double A[], double B[], int N) {
	int M = N;
	double mA[8192], mB[8192];
	int match = 16;
	for (int i = 0; i < M; i++) {
		mA[i] = A[i%N];
		if (i < match)
			mB[i] = B[i%N];
		else
			mB[i] = 0;
	}
	
	double test = 1e+60;
	for (int i = 0; i < N - match; i++) {
		double resize = mB[0] / mA[i];
		for (int j = i, k = 0; j < i + match; j++, k++) {
			if (mB[k] && mA[j] && fabs(mB[k]) < 32767) {
				resize = fabs(mB[k] / mA[j]);
			}
		}
		if (resize == 0)	continue;
//		printf("%d %lf\n", i, resize);
		double dot = 0, sumA = 0, sumB = 0;
		for (int j = i, k = 0; j < i + match; j++, k++) {
			double a = max(min(32767.0, round(resize * mA[j])), -32767.0);
			dot += a * mB[k];
			sumA += a * a, sumB += mB[k] * mB[k];
//			printf("%lf %lf\n", a, mB[k]);
		}
//		printf("%lf\n", sumA - 2*dot + sumB);
		test = min(test, sumA - 2*dot + sumB);
	}
	return test;
}
int main() {
	char s[1024];
	int R = 8000, N = 8000;
	double A[65536] = {}, B[65536] = {}, C[65536];
	scanf("%d %d", &R, &N);
	for (int i = 0; i < N; i++)
		scanf("%lf", &B[i]);
	double mn = -1;
	string best = "";
	for (int k = '9'; k >= '1'; k--) {
		for (int i = 'A'; i <= 'G'; i++) {
			for (int j = -1; j <= 1; j++) {
				string s;
				s += string(1, i);
				if (j == 1)		s += '#';
				if (j == -1)	s += 'b';
				s += string(1, k);
				make(s.c_str(), A, R, min(N, 128));
				double f = test(A, B, min(N, 128));
				if (mn < 0 || f < mn)
					mn = f, best = s;
			}
		}
	}
	printf("%d %d\n", R, N);
	make(best.c_str(), A, R, N);
	for (int i = 0; i < N; i++) {
		int f = round(A[i]);
		printf("%d ", f);
	}
	puts("");
	return 0;
}
/*
8000 8
0 10029 19635 28416 32767 32767 32767 32767
*/

