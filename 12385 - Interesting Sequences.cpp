#include <stdio.h>
#include <string.h>
int main() {
	int T, N, i, x;
	int set[100001];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		memset(set, -1, sizeof(set));
		int Ans = 0, last = -1;
		for(i = 0; i < N; i++) {
			scanf("%d", &x);
			if(set[x] >= last && set[x] != 0xffffffff) {
				Ans++, last = i;
			}
			set[x] = i;
		}
		printf("%d\n", Ans);
	}
    return 0;
}
