#include <stdio.h>
#include <string.h>
#define MaxL 1000005
char A[MaxL], B[MaxL];
int P[MaxL];
void KMPTable(const char *A) {
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
int KMPMatching(char A[], char B[], int la, int lb) { // B in A
	KMPTable(B);
	static int i, j, Alen, Blen;
	Alen = la, Blen = lb;
	for(i = 0, j = -1; i < Alen; i++) {
		while(j >= 0 && B[j+1] != A[i])
			j = P[j];
		if(B[j+1] == A[i])	j++;
		if(j == Blen-1)
		    return 1;
	}
	return 0;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", A);
        int la = strlen(A);
        int l = 1, r = la, m, i, j;
        while(l <= r) {
            m = (l+r)>>1;
            for(i = m-1, j = 0; i >= 0; i--, j++)
                B[j] = A[i];
            B[j] = '\0';
            if(KMPMatching(A, B, la, m))
                l = m+1/*, printf("%s %d\n", B, m)*/;
            else
                r = m-1;
        }
        for(i = l-2; i >= 0; i--)
            putchar(A[i]);
        puts("");
    }
    return 0;
}
