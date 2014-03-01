#include<stdio.h>
int main() {
	int T, x, y;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &x, &y);
		if(x < y)		puts("<");
		else if(x > y)	puts(">");
		else	puts("=");
	}
    return 0;
}
