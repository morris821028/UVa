#include<stdio.h>
#include<string.h>
#define    MaxN 5000001
void RadixSort(int *A, int *B, int n) {
    int a, x, d, *T, C[256];
    for(x = 0; x < 4; x++) {
        d = x*8;
        for(a = 0; a < 256; a++)        C[a] = 0;
        for(a = 0; a < n; a++)        C[(A[a]>>d)&255]++;
        for(a = 1; a < 256; a++)    C[a] += C[a-1];
        for(a = n-1; a >= 0; a--)    B[--C[(A[a]>>d)&255]] = A[a];
        T = A, A = B, B = T;
    }    
}
char S[5000000];
int S0[MaxN], S1[MaxN];
main() {
    int n = 0, a, l, r = 0, g = 0;
    gets(S), l = strlen(S);
    for(a = 0; a < l; a++) {
		if(S[a] >= '0')
			r = r*10 + S[a]-'0', g = 1;
		else
			S0[n++] = r, r = 0, g = 0;
	}
	if(g) S0[n++] = r;
    RadixSort(S0, S1, n);
    for(a = 0; a < n; a++)
		printf("%d ", S0[a]);
    puts("");
    return 0;
}
