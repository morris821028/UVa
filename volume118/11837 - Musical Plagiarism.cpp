#include <stdio.h>
#include <algorithm>
using namespace std;
int notes[128] = {};
int kmpTable[500005];
void KMPtable(int *P, int len) {
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
int KMPmatching(int T[], int P[], int tlen, int plen) {
    for(int i = 0, j = -1; i < tlen; i++) {
        while(j >= 0 && P[j+1] != T[i])
            j = kmpTable[j];
        if(P[j+1] == T[i])  j++;
        if(j == plen-1) {
            j = kmpTable[j];
            return i;
        }
    }
    return -1;
}
int main() {
	int M, T;
	int A[100005], B[10005];
	char s[10];
	notes['C'] = 0, notes['D'] = 2;
	notes['E'] = 4,	notes['F'] = 5;
	notes['G'] = 7,	notes['A'] = 9;
	notes['B'] = 11;
	while(scanf("%d %d", &M, &T) == 2 && M + T) {
		int prev, x;
		for(int i = 0; i < M; i++) {
			scanf("%s", &s);
			x = (notes[s[0]] + (s[1] == '#') - (s[1] == 'b') + 12)%12;
			if(i)	A[i - 1] = (prev - x + 12)%12;
			prev = x;
		}
		for(int i = 0; i < T; i++) {
			scanf("%s", &s);
			x = (notes[s[0]] + (s[1] == '#') - (s[1] == 'b') + 12)%12;
			if(i)	B[i - 1] = (prev - x + 12)%12;
			prev = x;
		}
		KMPtable(A, M - 1);
		puts( KMPmatching(A, B, M - 1, T - 1) >= 0 ? "S" : "N");
	}
	return 0;
}
