#include<stdio.h>
#include<string.h>
int DP[251][251], Ans = 0;
char AnsS[251], Print[251][251];
void Find(int x, int y, int now, char *A) {
	if(x == 0 || y == 0)	return;
	if(Print[x][y] == 1) {
		Find(x-1, y-1, now-1, A);
		AnsS[now] = A[x-1];
	} else if(Print[x][y] == 2)
		Find(x, y-1, now, A);
	else
		Find(x-1, y, now, A);
}
void LCS(char *A, int Al, char *B, int Bl) {
	DP[0][0] = DP[1][0] = DP[0][1] = 0;
	int a, b;
	for(a = 0; a < Al; a++) {
		for(b = 0; b < Bl; b++) {
			if(A[a] == B[b])
				DP[a+1][b+1] = DP[a][b]+1, Print[a+1][b+1] = 1;
			else {
				if(DP[a+1][b] >= DP[a][b+1])
					DP[a+1][b+1] = DP[a+1][b], Print[a+1][b+1] = 2;
				else
					DP[a+1][b+1] = DP[a][b+1], Print[a+1][b+1] = 3;
			}
		}
	}
	if(DP[Al][Bl] >= Ans) {
		Ans = DP[Al][Bl];
		Find(Al, Bl, Ans-1, A);
		AnsS[Ans] = '\0';
	}
}
main() {
	char A[502], B[502];
	while(scanf("%s %s", A, B) == 2) {
		int Al = strlen(A), Bl = strlen(B), a, b;
		for(a = 0, b = Al; a < Al; a++, b++)
			A[b] = A[a];
		for(a = 0, b = Bl; a < Bl; a++, b++)
			B[b] = B[a];
		Ans = 0;
		for(a = Al-1; a >= 0; a--)
			LCS(A+a, Al, B, Bl);
		puts(Ans ? AnsS : "no");
		printf("%.2lf\n", (double)Ans*2/(Al+Bl));
	}
	return 0;
}
