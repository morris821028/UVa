#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 100005
char P[MAXN], T[MAXN];
int kmpTable[MAXN];
void KMPtable(const char *P, int len) {
    int i, j;
    kmpTable[0] = -1, i = 1, j = -1;
    while (i < len) {
        while (j >= 0 && P[j+1] != P[i])
            j = kmpTable[j];
        if (P[j+1] == P[i])
            j++;
        kmpTable[i++] = j;
    }
}
int KMPmatching(const char *T, int tlen, const char *P, int plen) {
	KMPtable(P, plen);
	int i, j;
    for (i = 0, j = -1; i < tlen; i++) {
        while (j >= 0 && P[j+1] != T[i])
        	j = kmpTable[j];
        if (P[j+1] == T[i])  j++;
        if (j == plen-1)
        	return j;
    }
    return j;
}
char* shortestPalindrome(char* s) {
	int n = strlen(s);
	char *inv = (char *) malloc(n*sizeof(char));
	for (int i = 0, j = n-1; i < n; i++, j--)
		inv[i] = s[j];
    int overlap = n - KMPmatching(inv, n, s, n) - 1;
    char *ret = (char *) malloc((n+overlap+1)*sizeof(char));
    for (int i = 0; i < n; i++)
    	ret[i] = s[n-i-1];
    for (int i = 0; i < overlap; i++)
    	ret[n+i] = s[n-overlap+i];
    ret[n+overlap] = '\0';
    puts(ret);
    return ret;
}
int main() {
	shortestPalindrome("aacecaaa");
	shortestPalindrome("abcd");
	shortestPalindrome("aba");
	shortestPalindrome("abbacd");
	return 0;
}

