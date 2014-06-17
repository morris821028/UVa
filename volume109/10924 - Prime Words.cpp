#include <stdio.h>
int Prime[2000] = {};
void sieve() {
	int i, j;
	for(i = 2; i < 2000; i++) {
		if(Prime[i] == 0) {
			for(j = 2; i*j < 2000; j++)
				Prime[i*j] = 1;
		}
	}
}
int main() {
	sieve();
	char str[100];
	while(scanf("%s", str) == 1) {
		int sum = 0, i;
		for(i = 0; str[i]; i++) {
			if(str[i] >= 'a' && str[i] <= 'z')
				sum += str[i]-'a'+1;
			else
				sum += str[i]-'A'+27;
		}
		if(Prime[sum] == 0)
			puts("It is a prime word.");
		else
			puts("It is not a prime word.");
	}
    return 0;
}
