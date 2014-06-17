#include<stdio.h>
int main() {
	int T, N, P;
	scanf("%d", &T);
	while(T--) {
		int Day[3651] = {0}, i, x, tmp;
		scanf("%d %d", &N, &P);
		for(i = 0; i < P; i++) {
			scanf("%d", &x), tmp = x;
			while(x <= N)
				Day[x] = 1, x = x+tmp;
		}
		int count = 0;
		for(i = 1; i <= N; i++)
			if(Day[i] == 1 && i%7 != 0 && i%7 != 6)
				count++;
		printf("%d\n", count);
	}
    return 0;
}
