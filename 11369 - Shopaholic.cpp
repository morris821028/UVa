#include <stdio.h>

int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
	int t, n, p;
	scanf("%d", &t);
	while(t--) {
		ReadInt(&n);
		int count[20001] = {}, sum = 0;
		while(n--) {
			ReadInt(&p);
			count[p]++;
		}
		int flag = 0, i, j;
		for(i = 20000; i >= 1; i--) {
			for(j = 0; j < count[i]; j++) {
				flag++;
				if(flag%3 == 0)
					sum += i;
			}
		}
		printf("%d\n", sum);
	}
    return 0;
}
