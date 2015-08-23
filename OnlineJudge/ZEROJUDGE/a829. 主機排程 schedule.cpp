#include <bits/stdc++.h> 
using namespace std;

int main() {
	int testcase, D, N;
	int Td, Ts, Th, Rc, Rr, Rb;
	scanf("%d %d", &testcase, &D);
	while (testcase--) {
		scanf("%d", &N);
		// D <= 1000
		int mark[65536][3] = {}, TT = D*24;
		for (int i = 0; i < N; i++) {
			scanf("%d %d %d %d %d %d", &Td, &Ts, &Th, &Rc, &Rr, &Rb);
			Td--;
			int st = Td * 24 + Ts;
			int ed = st + Th;
			for (int j = st; j < ed; j++)
				mark[j%TT][0] += Rc, mark[j%TT][1] += Rr, mark[j%TT][2] += Rb;
		}
		scanf("%*d");
		for (int i = 0; i < 3; i++) {
			int mx = 0;
			for (int j = 0; j < 65536; j++)
				mx = max(mx, mark[j][i]);
			printf("%d%c", mx, i == 2 ? '\n' : ' ');
		} 
	}
	return 0;
}
