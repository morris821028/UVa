#include<stdio.h>
int main() {
	int T, L, W, H, C = 0;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d %d", &L, &W, &H);
		printf("Case %d: ", ++C);
		if(L > 20 || W > 20 || H > 20)
			puts("bad");
		else
			puts("good");
	}
    return 0;
}
