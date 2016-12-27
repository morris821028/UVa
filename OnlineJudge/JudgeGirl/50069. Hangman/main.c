#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hangman.h"

int main() {
	int testcase;
	assert(scanf("%d", &testcase) == 1);
	while (testcase--) {
		char s[MAXL], in[MAXGL];
		int G;
		assert(scanf("%s %d", s, &G) == 2);
		assert(scanf("%s", in) == 1);
		Hangman *h = newGame(s, G);
		for (int i = 0; in[i]; i++) {
			int r = guess(h, in[i]);
			printf("%d ", r), printStatus(h);
			if (r < 0) {
				puts("You Lose");
				break;
			} else if (solved(h)) {
				puts("You Win");
				break;
			} else if (in[i+1] == '\0') {
				puts("You Quit");
				break;
			}
		}
	}
	return 0;
}
