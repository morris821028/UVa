// dynamic programming
#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
	int N, M, x;
	while(scanf("%d %d", &N, &M) == 2 && N+M) {
		int prevLine1 = 0, prevLine2 = 0, tmp;
		for(int i = 0; i < N; i++) {
			int prevNum1 = 0, prevNum2 = 0;
			for(int j = 0; j < M; j++) {
				scanf("%d", &x);
				tmp = prevNum1;
				prevNum1 = max(prevNum1, x + prevNum2);
				prevNum2 = tmp;
			}
			tmp = prevLine1;
			prevLine1 = max(prevLine1, prevNum1 + prevLine2);
			prevLine2 = tmp;
		}
		printf("%d\n", prevLine1);
	}
	return 0;
}
