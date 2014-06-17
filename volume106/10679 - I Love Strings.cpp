#include <stdio.h>
#include <string.h>

char S[100001], T[10001];
int P[10001];
void KMP_Table(const char *A) {
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
int KMP_Match(const char *T, const char *S) {
    int i, j;
    int Tlen, Slen;
    Tlen = strlen(T), Slen = strlen(S);
    KMP_Table(T);
    for(i = 0, j = -1; i < Slen; i++) {
        while(j >= 0 && T[j+1] != S[i])
            j = P[j];
        if(T[j+1] == S[i])
            j++;
        if(j == Tlen-1) {
            return 1;
        }
    }
    return 0;
}
int main() {
    int t, q;
    scanf("%d", &t);
    getchar();
    while(t--) {
        gets(S);
        scanf("%d", &q);
        getchar();
        while(q--) {
            gets(T);
            if(KMP_Match(T, S) == 1)
                puts("y");
            else
                puts("n");
        }
    }
    return 0;
}
