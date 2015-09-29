#include<stdio.h>

int main() {
    int n, a[10000];
    while (scanf("%d",&n) == 1) {
    	for (int i = 0; i < n; i++)
			scanf("%d", &a[n-i-1]);
    	for (int i = 0; i < n; i++)
    		printf("%d%c", a[i], i == n-1 ? '\n' : ' ');
	}
	return 0;
}
