#include<stdio.h>
#include<stdlib.h>
main() {
	int N, score;
	while(scanf("%d",&N)==1) {
		score = 0;
		if(N >= 40) puts("100");
		else {
			if(N < 10) score = N*6;
			else if(N >= 10 && N < 20) score = N%10*2 + 60;
			else score = N%20 + 80;
						printf("%d\n", score);
		}
	}
	return 0;
}
