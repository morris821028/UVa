#include<stdio.h>
short Sum[1000001];
int main() {
	int T, M, i;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &M);
		getchar();
		char x, y;
		for(i = 0; i < M; i++) {
			x = getchar();
			getchar();
			y = getchar();
			getchar();
			Sum[i] = x + y - 96;
		}
		for(i = M-1; i >= 1; i--)
			if(Sum[i] >= 10) {
				Sum[i-1] += Sum[i]/10;
				Sum[i] %= 10;
			}
		printf("%d", Sum[0]);
		for(i = 1; i < M; i++)
			printf("%c", Sum[i]+'0');
		puts("");
		if(T)	puts("");
	}
    return 0;
}
