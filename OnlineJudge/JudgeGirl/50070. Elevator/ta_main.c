#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "elevator.h"


int main(){
	int u, d, F, N;
	char mv[MAXL];
	struct Elevator *elevator;
	
	assert(scanf("%d", &N) == 1);
	for(int n = 1; n <=N; n++){
		assert(scanf("%d %d %d", &u, &d, &F) == 3);
		assert(scanf("%s", mv) == 1);

		elevator = newElevator(u, d, F);
	
		int L = strlen(mv);
		for(int l = 0; l < L; l++){
			int x;
			if (mv[l] == 'U') x = up(elevator);
			if (mv[l] == 'D') x = down(elevator);
		
			if (x == 0) printf("Invalid\n");
			else if (x == 1) printf("Valid %d\n", getPosition(elevator));
			else if (x == -1) {
				printf("Broken\n");
				break;
			} else {
				assert(0);
			}

		}	
	
		for(int i = 1; i <= F; i++)
			if (visited(elevator, i)) printf("%d\n", i);

		free(elevator);
	}
	return 0;
}

