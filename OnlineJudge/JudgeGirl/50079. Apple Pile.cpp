#include <stdio.h>

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	int tot = (a+b)*(b-a+1)/2;
	int par = a + b + 2*(b-a-1);
	printf("%d\n%d\n", tot, par);
  	return 0;
}
