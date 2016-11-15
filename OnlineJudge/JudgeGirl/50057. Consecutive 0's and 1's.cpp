#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char dict[1<<8][9];
static char whsp[64], space, prev;
void build() {
	const int n = 1<<8;
	for (int i = 0; i < n; i++) {
		for (int j = 7; j >= 0; j--)
			dict[i][7-j] = ((i>>j)&1) + '0';
		dict[i][8] = '\0';
	}
	memset(whsp, ' ', sizeof(whsp));
}
void print(uint32_t n) {
	for (int i = 32-8; i >= 0; i -= 8) {
		char *ptr = dict[(n>>i)&((1<<8)-1)];
		while (*ptr) {
			if (*ptr != prev) {
				putchar('\n');
				whsp[space] = '\0';
				fputs(whsp, stdout);
				whsp[space] = ' ';
			}			
			prev = *ptr;	
			putchar(prev);
			ptr++, space++;
			if (space >= 40)	space = 0;
		}
	}
}
int main() {
	build();
	int n, x;
	while (scanf("%d", &n) == 1) {
		space = 0, prev = '0';
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			print(x);
		}
		puts("");
	}
	return 0;
}

