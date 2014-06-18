#include <stdio.h>

int main() {
	int t, n, Case = 0;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int max = 0, c;
		while(n--) {
			scanf("%d", &c);
			if(max < c)
				max = c;
		}
		printf("Case %d: %d\n", ++Case, max);
	}
    return 0;
}
