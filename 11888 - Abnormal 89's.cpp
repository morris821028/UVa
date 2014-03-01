#include<stdio.h>
#include<string.h>
#define MaxL 200005
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
	int i, j, Alen, Blen, flag = -1, match;
	Alen = strlen(A), Blen = strlen(B);
	for(i = 0, j = -1; i+(Blen-(j+1)) <= Alen; i++) {
		while(j >= 0 && B[j+1] != A[i])
			j = P[j];
		if(B[j+1] == A[i])	j++;
		if(j == Blen-1) {	
			match = i-Blen+1;
			if(match)
				return match;
			flag = 0;
			j = P[j];
			continue;
		}
	}
	return flag;
}
void Solve(char A[]) {
	int Alen = strlen(A), Blen = Alen;
	int i, j;
	for(i = 0, j = Blen-1; i < Alen; i++, j--)
		B[j] = A[i];
	B[Blen] = '\0';
	for(i = 0, j = Alen; i < Alen; i++, j++)
		A[j] = A[i];
	A[j] = '\0';
	int match = KMPMatching(A, B);
	if(match == 0 || match == Alen)
		puts("palindrome");
	else if(match == -1)
		puts("simple");
	else
		puts("alindrome");
}
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", A);
		Solve(A);
	}
    return 0;
}
