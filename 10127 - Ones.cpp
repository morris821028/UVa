#include <stdio.h>
int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		int i, tmp = 1;
		for(i = 1; ; i++) {
			if(tmp%n == 0)	break;
			tmp = tmp*10 + 1;
			tmp %= n;
		}
		printf("%d\n", i);
	}
    return 0;
}
