#include <stdio.h>
#include <string.h>
char A[1024], W[500005], S[500005];
int kmpTable[500005];
void KMPtable(char *P, int len) {
    int i, j;
    kmpTable[0] = -1, i = 1, j = -1;
    while(i < len) {
        while(j >= 0 && P[j+1] != P[i])
            j = kmpTable[j];
        if(P[j+1] == P[i])
            j++;
        kmpTable[i++] = j;
    }
}
int KMPMatching(char T[], char P[], int tlen, int plen) {
    int i, j;
    int matchCnt = 0;
    for(i = 0, j = -1; i < tlen; i++) {
        while(j >= 0 && P[j+1] != T[i])
            j = kmpTable[j];
        if(P[j+1] == T[i])  j++;
        if(j == plen-1) {
            matchCnt++;
            j = kmpTable[j];
            if(matchCnt >= 2)
                return matchCnt;
        }
    }
    return matchCnt;
}
char E[500005];
int main() {
    int testcase;
    int i, j, k;
    scanf("%d", &testcase);
    while(getchar() != '\n');
    while(testcase--) {
        gets(A);
        gets(W);
        gets(S);
        int Alen = strlen(A);
        int Wlen = strlen(W);
        int Slen = strlen(S);
        int CHAR[1024] = {};
        for(i = 0; A[i]; i++)
            CHAR[A[i]] = i;
        int ret[1024], ridx = 0;
        for(i = 0; i < Alen; i++) {
            for(j = 0; j < Wlen; j++)
                E[j] = A[(CHAR[W[j]]+i)%Alen];
            E[Wlen] = '\0';
            KMPtable(E, Wlen);
            int cnt = KMPMatching(S, E, Slen, Wlen);
            if(cnt == 1)
                ret[ridx++] = i;
        }
        if(ridx == 0)
            puts("no solution");
        else if(ridx == 1)
            printf("unique: %d\n", ret[0]);
        else {
            printf("ambiguous:");
            for(i = 0; i < ridx; i++)
                printf(" %d", ret[i]);
            puts("");
        }
    }
    return 0;
}
