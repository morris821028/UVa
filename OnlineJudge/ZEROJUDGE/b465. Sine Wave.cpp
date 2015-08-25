#include <bits/stdc++.h>
using namespace std;

int main() {
	const double pi = acos(-1);
	int F, T, R, N;
	scanf("%d %d", &F, &T);
	R = 8000, N = T * R;
	printf("%d %d\n", R, N);
	double d = F * 2 * pi / R;
	for (int i = 0; i < N; i++) {
		int f = round(32767 * sin((double)i * d));
		printf("%d%c", f, i == N-1 ? '\n' : ' ');
	}
	return 0;
}
