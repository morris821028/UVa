#include<stdio.h>
#include<string.h>
#define MaxL 100005
char A[MaxL], B[MaxL];
int P[MaxL];
void KMPTable(char *A) {
	int i, j;
	P[0] = -1, i = 1, j = -1;
	while(A[i]) {
		while(j >= 0 && A[j+1] != A[i])
			j = P[j];
		if(A[j+1] == A[i])
			j++;
		P[i++] = j;
	}
}
int KMPMatching(char A[], char B[]) {
	KMPTable(B);
	int i, j, Alen, Blen;
	Alen = strlen(A), Blen = strlen(B);
	for(i = 0, j = -1; i < Alen; i++) {
		while(j >= 0 && B[j+1] != A[i])
			j = P[j];
		if(B[j+1] == A[i])	j++;
	}
	return j;
}
void Solve(char A[]) {
	
	int Alen = strlen(A), Blen = Alen;
	int i, j;
	for(i = 0, j = Blen-1; i < Alen; i++, j--)
		B[j] = A[i];
	B[Blen] = '\0';
	int tail = KMPMatching(A, B);
	for(i = Blen-1; i > tail; i--)
		printf("%c", B[i]);
	printf("%s\n", B);
	
}
int main() {
	while(scanf("%s", A) == 1)
		Solve(A);
    return 0;
}
