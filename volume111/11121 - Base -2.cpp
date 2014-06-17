#include<stdio.h>
#include<stdlib.h>
void Base_2(int n) {
	if(n > 0) {
		Base_2(n/(-2));
		printf("%d", n%2);
	}
	if(n < 0) {
		Base_2(n/(-2)+(n%(-2) != 0));
		printf("%d", abs(n%(-2)));
	}
}
int main() {
	int t, C = 0, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("Case #%d: ", ++C);
		if(n == 0)	puts("0");
		else Base_2(n), puts("");
	}
    return 0;
}
