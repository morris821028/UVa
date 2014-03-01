#include<stdio.h>
struct data{
	long long x, y;
}D[3], t;
main() {
	while(scanf("%lld %lld %lld", &D[0].x, &D[1].x, &D[2].x) == 3) {
		D[0].y = 0, D[1].y = 1, D[2].y = 2;
		if(D[0].x > D[2].x) t = D[0], D[0] = D[2], D[2] = t;
		if(D[1].x > D[2].x) t = D[1], D[1] = D[2], D[2] = t;
		if(D[0].x > D[1].x) t = D[0], D[0] = D[1], D[1] = t;
		D[1].x += D[0].x;
		if(D[1].x > D[2].x)	printf("%c\n",D[1].y + 'A');
		else printf("%c\n",D[2].y + 'A');
	}
	return 0;
}
