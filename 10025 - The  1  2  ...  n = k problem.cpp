#include <stdio.h>
#include <stdlib.h>
int main() {
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		n = abs(n);
		int k;
		for(k = 1; ; k++) {
			if(k*(k+1)/2 >= n && (k*(k+1)/2-n)%2 == 0)
				break;
		}
		printf("%d\n", k);
		if(t)	puts("");
	}
    return 0;
}
