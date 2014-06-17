#include<stdio.h>
int main() {
	int n, m, e, tmp;
	int i, j;
	while(scanf("%d %d %d", &n, &m, &e) == 3) {
		if(n%m == 0) {puts("0");continue;} 
		int t2 = 4;
		for(i = 1; i <= e; i++) {
			for(j = 1; j <= 3; j++) {
				if(i == 1 && j == 1)	continue;
				t2 %= m;
				tmp = (t2*(n+1)-1)%m;
				t2 *= 2;
				if(!tmp)	break;
			}
			if(j != 4)	break;
		}
		printf("%d\n", i == e+1 ? -1 : i);
	}
	return 0;
}
