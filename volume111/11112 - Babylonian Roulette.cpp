#include <stdio.h>
#include <stdlib.h>

int main() {
	int pot, bet, fpot;
	while(scanf("%d %d %d", &pot, &bet, &fpot) == 3) {
		if(pot + bet + fpot == 0)
			break;
		if(abs(fpot - pot)%bet) {
			puts("No accounting tablet");
			continue;
		}
		int diff = abs(fpot - pot) / bet;
		int cnt = diff/3 + (diff%3 ? 1 : 0);
		printf("%d\n", cnt);
	}
	return 0;
}
