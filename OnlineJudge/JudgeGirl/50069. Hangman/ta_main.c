#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hangman.h"

int main(){
	char answer[MAXL], str[MAXGL];
	int N, G;

	assert(scanf("%d", &N) == 1);

	while(N--){
		assert(scanf("%s %d", answer, &G) == 2);
		assert(scanf("%s", str) == 1);
		int L = strlen(str);

		//assert(1 <= strlen(answer) && strlen(answer) <= 100);
		//assert(1 <= L && L <= 200);
		//assert(1 <= G && G <= 100);
		Hangman *hangman = newGame(answer, G);

		for(int i = 0; i < L; i++){
			int x = guess(hangman, str[i]);
			printf("%d ", x);
			printStatus(hangman);

			if (solved(hangman)){
				printf("You Win\n");
				break;
			}
			if (x == -1){
				printf("You Lose\n");
				break;
			}

			if (i == L - 1)
				printf("You Quit\n");
		}
		free(hangman);
	}
	return 0;
}
