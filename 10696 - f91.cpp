#include<stdio.h>
int main() {
	int n;
	while(scanf("%d", &n) == 1 && n) {
		printf("f91(%d) = %d\n", n, n > 100 ? n-10 : 91);
	}
    return 0;
}
