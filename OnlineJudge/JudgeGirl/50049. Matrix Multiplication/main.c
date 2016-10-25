#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix_multiplication.h"
#define MAX 65536
static int A_elements[MAX], A_rowind[MAX], A_colind[MAX];
static int B_elements[MAX], B_rowind[MAX], B_colind[MAX];
char stk[12];
char buf[1<<20], *ptr = buf;
void myPrint(int x, char end){
		int nstk = 0;
		int isNeg = 0;
		stk[nstk++] = end;
		if(!x) stk[nstk++] = '0';
		if(x < 0) isNeg = 1, x*=-1;
		while(x){
				stk[nstk++] = (x % 10) + '0', x /= 10;
		}
		if(isNeg) stk[nstk++] = '-';
		while(nstk){
				if(buf + (1<<20) - ptr < 1<<4){
						*ptr = '\0';
						printf("%s", buf), ptr = buf;
				}
				*ptr = stk[--nstk], ptr++;
		}
		return;
}

void endPrint(){
		*ptr = '\0';
		printf("%s", buf), ptr = buf;
}
int main(int argc, char const *argv[])
{
	int N, M, S;// = 3, M = 5;
	assert(scanf("%d %d %d", &N, &M, &S) == 3);
	int *ptrA[3];// = {{5, 5, 5}, {0, 1, 3}, {0, 1, 3}};
	int *ptrB[3];// = {{1, 2, 3}, {3, 1, 0}, {3, 1, 0}};
	ptrA[0] = A_elements, ptrA[1] = A_rowind, ptrA[2] = A_colind;
	ptrB[0] = B_elements, ptrB[1] = B_rowind, ptrB[2] = B_colind;
	for(int i = 0; i < N; ++i)
		assert(scanf("%d", &A_elements[i]) == 1);
	for(int i = 0; i < N; ++i)
		assert(scanf("%d", &A_rowind[i]) == 1);
	for(int i = 0; i < N; ++i)
		assert(scanf("%d", &A_colind[i]) == 1);
	for(int i = 0; i < M; ++i)
		assert(scanf("%d", &B_elements[i]) == 1);
	for(int i = 0; i < M; ++i)
		assert(scanf("%d", &B_rowind[i]) == 1);
	for(int i = 0; i < M; ++i)
		assert(scanf("%d", &B_colind[i]) == 1);
	int *result = malloc(S*S*sizeof(int));
	matrix_multiplication(N, ptrA, M, ptrB, S, result);

	for (int i = 0; i < S; ++i){
		for(int j = 0; j < S; ++j){
			//printf("%d%c", result[i*S+j], " \n"[j == S - 1]);
			myPrint(result[i * S + j], j == S - 1? '\n': ' ');
		}
	}
	endPrint();
	return 0;
}
