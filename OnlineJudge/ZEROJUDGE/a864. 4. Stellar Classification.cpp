#include <bits/stdc++.h>
using namespace std;
const double BV[] = {-0.350, -0.250, -0.000, 0.250, 0.500, 1.000, 1.500, 2.000};
const char BVS[][2] = {"O", "B", "A", "F", "G", "K", "M"};
int main() {
	char s[1024];
	double mB, mV;
	while (scanf("%s", s) == 1) {
		if (!strcmp(s, "END"))
			break;
		scanf("%lf %lf", &mB, &mV);
		int pos = 0;
		for (int i = 0; i < 7; i++) {
			if (BV[i] <= mB - mV && mB - mV < BV[i+1])
				pos = i;
		}
		printf("%s %.2lf %s\n", s, mB - mV, BVS[pos]);
	}
	return 0;
}
