#include<stdio.h>
int main() {
	int matrix[101][101], n, i, j;
	while(scanf("%d", &n) == 1 && n) {
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf("%d", &matrix[i][j]);
		int R[100] = {0}, C[100] = {0};
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				C[i] += matrix[i][j];
				R[i] += matrix[j][i];
			}
		}
		int ER = 0, EC = 0, er, ec;
		for(i = 0; i < n; i++) {
			if(R[i]&1)	ER++, er = i;
			if(C[i]&1)	EC++, ec = i;
		}
		if(ER == 0 && EC == 0)
			puts("OK");
		else if(ER == 1 && EC == 1)
			printf("Change bit (%d,%d)\n", ec+1, er+1);
		else
			puts("Corrupt");
			
	}
    return 0;
}
