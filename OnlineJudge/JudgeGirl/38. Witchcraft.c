#include <stdio.h>

int a, b, c, G;
long long A, B, C;
int f(int id, int va, int vb, int vc, long long g) {
	if (id == 3 || g > G)	return g == G;
	if (id == 0) {
		for (int i = 0; i <= va && g+i*A <= G; i++)
			if(f(id+1, va-i, vb, vc, g+i*A))	
				return 1;
	}
	if (id == 1) {
		for (int i = 0; i <= vb && g+i*B <= G; i++)
			if(f(id+1, va, vb-i, vc, g+i*B))
				return 1;
	}
	if (id == 2) {
		for (int i = 0; i <= vc && g+i*C <= G; i++)
			if(f(id+1, va, vb, vc-i, g+i*C))
				return 1;
	}
	return 0;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &G);
		scanf("%d %d %d", &a, &b, &c);
		scanf("%lld %lld %lld", &A, &B, &C);
		puts(f(0, a, b, c, 0) ? "yes" : "no");
	}
	return 0;
}

