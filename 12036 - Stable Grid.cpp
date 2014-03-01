#include <stdio.h>
int main() {
	int t, n, x, Case = 0;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int count[101] = {};
		int i, j, flag = 1;
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				scanf("%d", &x);
				count[x]++;
				if(count[x] > n)
					flag = 0;
			}
		}
		printf("Case %d: ", ++Case);
		if(flag == 1)	puts("yes");
		else			puts("no");
	}
    return 0;
}
