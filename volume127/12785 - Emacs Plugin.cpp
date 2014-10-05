#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;

#define MAXN 100005
char P[MAXN], T[MAXN];
int kmpTable[MAXN];
void KMPtable(const char *P, int len) {
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
int KMPmatching(const char *T, int tlen, const char *P, int plen) {
    for(int i = 0, j = -1; i < tlen; i++) {
        while(j >= 0 && P[j+1] != T[i])
            j = kmpTable[j];
        if(P[j+1] == T[i])  j++;
        if(j == plen-1)
        	return i;
    }
    return -1;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int n, plen, tlen;
	string token;
	while (scanf("%d", &n) == 1) {
		while (getchar() != '\n');
		gets(P);
		plen = strlen(P);
		for (int i = 0; i < n; i++) {
			gets(T);
			for (int j = 0; T[j]; j++) {
				if (T[j] == '*')
					T[j] = ' ';
			}
			stringstream sin(T);
			int start = 0;
			while (sin >> token) {		
				KMPtable(token.c_str(), token.length());
				int test = KMPmatching(P + start, plen - start, token.c_str(), token.length());
//				printf("%s %d %s\n", token.c_str(), test, P + start);
				if (test == -1)	 {start = -1; break;}
				start += test + 1;
			}
			puts(start == -1 ? "no" : "yes");
		}
	}
	return 0;
}
/*
4
heyhelloyou
hel*
*o*e
e*o
hello
1
hello
x

10
rwoeyhtdvtswftfguuujqxdxdqylkyqaahianzbejckxbgeybq
oexktdvtswftf*w*n*q*rvdloll*qr
kdd*ts*ftv**ur**cdx*qi
*dtlk
**q**g****a**n
*/
