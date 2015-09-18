#include <bits/stdc++.h>
using namespace std;

bitset<1048576> MM;
int main() {
	int R, C, Q;
	int lx, ly, rx, ry;
	scanf("%d %d", &R, &C);
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
		int cnt = 0;
		lx--, ly--, rx--, ry--;
		for (int p = lx; p <= rx; p++)
			for (int q = ly; q <= ry; q++)
				if (!MM[p*C+q])
					cnt++;
		printf("%d", cnt);
		for (int p = lx; p <= rx; p++)
			for (int q = ly; q <= ry; q++)
				if (!MM[p*C+q])
					printf(" (%d, %d)", p+1, q+1), MM[p*C+q] = 1;
		puts("");
	}
	return 0;
}
