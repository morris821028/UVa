#include<stdio.h>
int main() {
	int n, k;
	while(scanf("%d %d", &n, &k) == 2)
		puts((k == 0 && n != 0) || (k != 0 && n%k) ? "Impossib1e!" : "Ok!");
	return 0;
}
