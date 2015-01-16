#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
	freopen("new_years_resolution.txt", "r", stdin);
	freopen("out.txt", "w+", stdout); 
	int testcase, n, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int GP, GC, GF;
		int P[32], C[32], F[32];
		scanf("%d %d %d", &GP, &GC, &GF);
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d %d %d", &P[i], &C[i], &F[i]);
			
		int ret = 0;
		for (int i = (1<<n)-1; i >= 0 && !ret; i--) {
			int a = 0, b = 0, c = 0;
			for (int j = 0; j < n; j++) {
				if ((i>>j)&1) {
					a += P[j];
					b += C[j];
					c += F[j];
				}
			}
			ret |= a == GP && b == GC && c == GF;
		}
		printf("Case #%d: %s\n", ++cases, ret ? "yes" : "no");
	}
	return 0;
}
