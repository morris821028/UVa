#include <stdio.h>
#include <string.h>
int main() {
	int n, i, a, b;
	char s1[10], s2[10];
	while(scanf("%d", &n) == 1) {
		int l1 = 1, l2 = 1;
		for(i = 0; i < n; i++)
			l1 *= 10;
		for(i = 0; i < n/2; i++)
			l2 *= 10;
		for(i = 0; i < l1; i++) {
			if(i*i >= l1)	break;
			a = i*i/l2, b = i*i%l2;
			if(n == 2 && (a+b)*(a+b) == i*i) {
				sprintf(s1, "%01d%01d", a, b);
				sprintf(s2, "%02d", i*i);
				if(strcmp(s1, s2) == 0)
					printf("%s\n", s2);
			}
			if(n == 4 && (a+b)*(a+b) == i*i) {
				sprintf(s1, "%02d%02d", a, b);
				sprintf(s2, "%04d", i*i);
				if(strcmp(s1, s2) == 0)
					printf("%s\n", s2);
			}
			if(n == 6 && (a+b)*(a+b) == i*i) {
				sprintf(s1, "%03d%03d", a, b);
				sprintf(s2, "%06d", i*i);
				if(strcmp(s1, s2) == 0)
					printf("%s\n", s2);
			}
			if(n == 8 && (a+b)*(a+b) == i*i) {
				sprintf(s1, "%04d%04d", a, b);
				sprintf(s2, "%08d", i*i);
				if(strcmp(s1, s2) == 0)
					printf("%s\n", s2);
			}
		}
	}
    return 0;
}
