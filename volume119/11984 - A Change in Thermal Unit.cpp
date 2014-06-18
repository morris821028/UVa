#include<stdio.h>
int main() {
	int T, test = 0, C, d;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &C, &d);
		printf("Case %d: %.2lf\n", ++test, (double)C+d*5/9.0);
	}
    return 0;
}
