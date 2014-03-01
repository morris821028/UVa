#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main() {
	int A[11][11], B[11][11], i, j, k;
	while(scanf("%d", &A[1][1]) == 1) {
		int i;
		for(i = 1; i <= 10; i++)
			for(j = 1; j <= 10; j++) {
				if(i == 1 && j == 1)	continue;
				scanf("%d", &A[i][j]);
			}
		for(i = 1; i <= 10; i++)
			for(j = 1; j <= 10; j++) {
				scanf("%d", &B[i][j]);
			}
		int match[11] = {0}, Used[11] = {0};
		
		for(i = 0; i < 10; i++) {
			int wantB[11] = {0};
			int At[11] = {0};
			for(j = 1; j <= 10; j++) {/*loop A[]*/
				if(match[j] == 0) {
					for(k = 1; k <= 10; k++) {/**/
						if(Used[A[j][k]] == 0)
							break;
					}
					At[j] = A[j][k];
					wantB[A[j][k]]++;
				}
			}
			for(j = 1; j <= 10; j++)
				printf("%d ", At[j]);
			puts("*----At");
			for(j = 1; j <= 10; j++) {
				for(k = 1; k <= 10; k++) {
					if(wantB[k] == j)
						break;
				}
				if(k != 11)	break;
			}
			int choose = k;
			for(j = 1; j <= 10; j++) {
				if(At[B[choose][j]] == choose)
					break;
			}
			j = B[choose][j];
			Used[choose] = 1;
			match[j] = choose;
			printf("A%d,B%d\n", j, choose);
		}

	}
    return 0;
}

9 4 10 8 3 6 7 1
X5 10 8 4 9 3 2 6 1 7
6 2 9 8 10 3 1 7 5 4
X10 2 6 8 7 9 3 1 4 5
6 3 9 2 10 8 4 5 7 1
9 8 4 1 6 3 10
X10 2 7 4 5 8 3 6 9 1
X7 3 9 8 10 2 1 6 5 4
X3 2 6 8 7 9 10 1 4 5
6 2 9 8 10 3 4 5 7 1

1 2 7 6 3 8 10 9 4 5
X2 7 3 6 10 9 1 5 4 8
X8 5 1 9 10 7 3 2 4 6
7 10 3 6 2 8 9 4 5 1
X7 2 1 6 10 8 3 5 4 9
5 3 1 4 10 8 2 7 6 9
X7 2 1 5 8 10 3 6 9 4
1 2 6 10 7 8 3 9 4 5
6 4 1 10 3 8 7 5 2 9
X2 9 4 5 10 8 1 6 3 7

