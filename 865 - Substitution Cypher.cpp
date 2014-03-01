#include <stdio.h>
#include <string.h>
int main() {
	int t, i;
	char A[100], B[100];
	scanf("%d", &t);
	getchar();
	getchar();
	while(t--) {
		gets(A);
		gets(B);
		char ASCII[128];
		int lenA = strlen(A), lenB = strlen(B);
		for(i = 0; i < 128; i++)
			ASCII[i] = i;
		for(i = 0; i < lenA || i < lenB; i++) {
			if(i >= lenA)	A[i] = ' ';
			if(i >= lenB)	B[i] = ' ';
			ASCII[A[i]] = B[i];
		}
		puts(B);
		puts(A);
		while(gets(A)) {
			if(A[0] == '\0')
				break;
			for(i = 0; A[i]; i++) {
				printf("%c", ASCII[A[i]]);
			}
			puts("");
		}
		if(t)
			puts("");
	}
    return 0;
}
