#include<stdio.h>
int main() {
	int T, Case = 0;
	scanf("%d", &T);
	while(T--) {
		int i, sum = 0, a, b;
		scanf("%d %d", &a, &b);
		if((a&1) == 0)	a++;
		for(i = a; i <= b; i += 2)
			sum += i;
		printf("Case %d: %d\n", ++Case, sum);
	}
    return 0;
}
