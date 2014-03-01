#include<stdio.h>
#include<string.h>
char x[1000001], y[1000001];
int main() {
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));
	int i, j, ti;
	for(i = 0; i <= 999999; i++) {
		if(i < 100000) {
			for(j = 0, ti = 10*i; j < 10; j++)
				y[ti+j] = y[i]+j;
		}
		if(i+y[i] <= 1000000)
			x[i+y[i]] = 1;
	}
	for(i = 1; i <= 1000000; i++)
		if(!x[i])
			printf("%d\n", i);
    return 0;
}
