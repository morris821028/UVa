#include <stdio.h>

int main() {
	int N, B, H, W;
	int P, i, a;
	while(scanf("%d %d %d %d", &N, &B, &H, &W) == 4) {
		int min = B+1;
		while(H--) {
			scanf("%d", &P);
			for(i = 0; i < W; i++) {
				scanf("%d", &a);
				if(a >= N && N*P < min)
					min = N*P;
			}
		}
		if(min == B+1)
			puts("stay home");
		else
			printf("%d\n", min);
	}
    return 0;
}
