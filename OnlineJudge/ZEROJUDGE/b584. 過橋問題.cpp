#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		int T[128] = {};
		for (int i = 0; i < n; i++)
			scanf("%d", &T[i]);
		sort(T, T+n);
		int A = T[0], B = T[1];
		int time = 0;
		while (n > 3) {
			int Y = T[n-2], Z = T[n-1];
			int s1 = B + A + Z + B;	// AB + A + YZ + B
			int s2 = Z + A + Y + A;// AZ + A + AY + A;
			time += min(s1, s2);
			n -= 2;
		}
		if (n == 1) {
			time += A;
		} else if (n == 2) {
			time += B; 
		} else if (n == 3) {
			time += A + B + T[2]; 
		}
		printf("%d\n", time);
	}
	return 0;
}

