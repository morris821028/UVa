#include<stdio.h>
int f(int n) {
	if(n < 10)	return n;
	int sum = 0;
	while(n) {
		sum += n%10;
		n /= 10;
	}
	return f(sum);
}
int main() {
	int n;
	while(scanf("%d", &n) == 1 && n)
		printf("%d\n", f(n));
    return 0;
}
