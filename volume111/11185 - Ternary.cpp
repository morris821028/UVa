#include<stdio.h>
void Base3(int n) {
	if(n == 0)	return ;
	Base3(n/3);
	printf("%d", n%3);
}
int main() {
	int n;
	while(scanf("%d", &n) == 1 && n >= 0) {
		if(n == 0)	{puts("0");continue;}
		Base3(n);
		puts("");
	}
    return 0;
}
