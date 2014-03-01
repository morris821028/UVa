#include<stdio.h>
#include<string.h>
int main() {
	char A[20], B[20];
	while(scanf("%s %s", A, B) == 2) {
		if(!strcmp(A, "0") && !strcmp(B, "0"))
			break;
		int i, C[20] = {0}, Al = strlen(A), Bl = strlen(B);
		for(i = 0; i < Al; i++)
			C[i] += A[Al-i-1] - 48;
		for(i = 0; i < Bl; i++)
			C[i] += B[Bl-i-1] - 48;
		int count = 0;
		for(i = 0; i < 20; i++) {
			if(C[i] >= 10) {
				C[i+1] += C[i]/10;
				C[i] %= 10;
				count++;
			}
		}
		if(!count)
			puts("No carry operation.");
		else {
			printf("%d carry operation%s.\n", count, count > 1 ? "s" : "");
		}
	}
    return 0;
}
