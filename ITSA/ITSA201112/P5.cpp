#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int F(int n) {
	if(n == 0)	return 0;
	return (n%10 == 0)+F(n/10);
}
int main() {
	int n, x, y;
	scanf("%d", &n);
	while(n--) {
		int sum = 0, i;
		scanf("%d %d", &x, &y);
		for(i = x+1;  i < y; i++) {
			sum += F(i);
		} 
		if(sum)
			printf("%d\n", sum);
		else
			puts("No Solution");
		if(n)	puts("");
	} 
    return 0;
}
