#include <bits/stdc++.h>
using namespace std;

int main() {
	int CNT[8] = {}, x; 
	while (scanf("%d", &x) == 1 && x)
		CNT[x]++;
	int sum = 0, n = 0;
	for (int i = 5; i >= 1; i--) {
		printf("%d (%2d) |", i, CNT[i]);
		for (int j = 0; j < CNT[i]; j++)
			printf("=");
		puts("");
		sum += CNT[i] * i, n += CNT[i];
	}
	printf("Average rating: %.4lf\n", (double)sum / n);
	return 0;
}
