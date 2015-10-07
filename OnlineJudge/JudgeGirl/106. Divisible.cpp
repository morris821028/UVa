#include <stdio.h>
#include <string.h>

int main() {
	char s[1024];
	while (scanf("%s", s) && s[0] != '-') {
		int n = strlen(s);
		int sum = 0, c[2] = {};
		for (int i = 0; i < n; i++)
			sum += s[i] - '0', c[i%2] += s[i] - '0';
		if ((s[n-1]-'0')%2)	printf("no");
		else				printf("yes");
		if (sum%3)	printf(" no");
		else		printf(" yes");
		if ((s[n-1]-'0')%5)	printf(" no");
		else				printf(" yes");
		if ((c[0] - c[1])%11)	puts(" no");
		else					puts(" yes");
	}
	return 0;
}

