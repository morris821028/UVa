#include<stdio.h>
#include<stdlib.h>
#define bin 4194304
int Mod = 2147483647/bin+1;
struct list {
    int v, next;
}X[500001];
int Bin[bin] = {}, prev, temp;
void InsBin(int n, int a) {
    int m = n/Mod;
    if(Bin[m] == 0) {
        X[a].v = n, X[a].next = 0;
        Bin[m] = a;return;
    }
    temp = Bin[m], prev = 0;
    while(X[temp].v < n) {
        prev = temp, temp = X[temp].next;
        if(temp == 0) break;
    }
	X[a].v = n, X[a].next = temp;
    if(prev != 0)	X[prev].next = a;
    else        Bin[m] = a;
    return;
}
void PrintBin() {
    int a, curr;
    for(a = 0; a < bin; a++) {
        curr = Bin[a];
        while(curr != 0) {
            printf("%d ", X[curr].v);
            curr = X[curr].next;
        }
    }
}
main() {
    int a, n;
    a = 1;
    while(scanf("%d", &n) == 1)
		InsBin(n, a), a++;
	PrintBin();
	puts("");
    return 0;
}
