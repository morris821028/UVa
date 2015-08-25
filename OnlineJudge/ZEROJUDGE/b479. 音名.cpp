#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
int main() {
	map<string, double> ff;
	ff["A"] = 440.00, ff["B"] = 493.88, ff["C"] = 261.63;
	ff["D"] = 293.66, ff["E"] = 329.63, ff["F"] = 349.23;
	ff["G"] = 392.00;
	for (int i = 0; i < 7; i++) {
		double w[] = {0, 2, 3, 5, 7, 8, 10};
		double f = exp(log(220) + (log(440) - log(220)) * w[i] / 12);
		if (i < 2)	f *= 2;
		ff[string(1, i+'A')] = f;
	}
	char s[1024];
	int R, N;
	int a = 0, b = 0, c = 0;
	double F;
	scanf("%s", s);
	for (int i = 0; s[i]; i++) {
		if (isupper(s[i]))		a = s[i];
		else if (isdigit(s[i]))	b = s[i] - '0';
		else if (s[i] == '#')	c = 1;
		else if (s[i] == 'b')	c = -1;
	} 
	F = ff[string(1, a)] * pow(2, b - 4);
	if (c == 1) {
		double Fnext;
		if (a == 'B')	
			Fnext = ff["C"] * pow(2, b - 3);
		else if (a == 'G')
			Fnext = ff["A"] * pow(2, b - 4);
		else
			Fnext = ff[string(1, a+1)] * pow(2, b - 4);
		F = exp((log(F) + log(Fnext))/2);
	} else if (c == -1) {
		double Fprev;
		if (a == 'C')	
			Fprev = ff["B"] * pow(2, b - 5);
		else if (a == 'A')
			Fprev = ff["G"] * pow(2, b - 4);
		else
			Fprev = ff[string(1, a-1)] * pow(2, b - 4);
		F = exp((log(F) + log(Fprev))/2);
	}
	R = 8000, N = R;
	printf("%d %d\n", R, N);
	double d = F * 2 * pi / R;
	for (int i = 0; i < N; i++)
		printf("%d ", (int) round(32767 * sin(i * d)));
	puts("");
	return 0;
}
