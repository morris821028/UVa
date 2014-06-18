#include<stdio.h>
void Print(unsigned n, int bit) {
	if(bit == 0)	return;
	Print(n>>1, bit-1);
	printf("%d", n&1);
}
int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		unsigned i, j;
		for(i = 0; i < (1<<n); i++) {
			unsigned tmp = 0;
			for(j = 0; j < n; j++) {
				tmp |= (((i>>j)^(i>>(j+1)))&1)<<j;
			}
			Print(tmp, n);
			puts("");
		}
	} 
    return 0;
}
