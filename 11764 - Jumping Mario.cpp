#include <stdio.h>
int main() {
	int n, t, last, Case = 0, x;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &last);
		int h = 0, l = 0;
		n--;
		while(n--) {
			scanf("%d", &x);
			if(x > last)	h++;
			if(x < last)	l++;
			last = x;
		}
		printf("Case %d: %d %d\n", ++Case, h, l);
	}
    return 0;
}
