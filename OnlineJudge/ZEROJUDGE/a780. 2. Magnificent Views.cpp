#include <bits/stdc++.h> 
using namespace std;

int main() {
	double fo, fe, Fa;
	while (scanf("%lf %lf %lf", &fo, &fe, &Fa) == 3 && fo)
		printf("%.2lf %.2lf\n", fo / fe, Fa / (fo / fe));
	return 0;
}
