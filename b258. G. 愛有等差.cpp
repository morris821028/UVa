#include<stdio.h>
#include<stdlib.h>
int Ki[50001], X[50001];
int Merge(int l, int m, int h) {
    int In1 = l, In2 = m+1;
    int a, b, Top = 0; 
    while(In1 <= m && In2 <= h)
        if(Ki[In1] < Ki[In2]) 
            X[Top++] = Ki[In1++];
        else X[Top++] = Ki[In2++];
    while(In1 <= m)	X[Top++] = Ki[In1++];
    while(In2 <= m)	X[Top++] = Ki[In2++];
    for(a = 0, b = l; a < Top; a++, b++) 
        Ki[b] = X[a]; 
} 
int MergeSort(int l, int h) {
    if(l< h) {
        int m = (l+h) /2;
        MergeSort(l  ,m);
        MergeSort(m+1,h); 
        Merge(l,m,h); 
    } 
} 
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int readint() {
    int c;
    while((c = readchar()) < '-');
    char neg = (c == '-');
    int x = neg?0:(c - '0');
    while((c = readchar()) >= '0') {
        x = (x << 3) + (x << 1) + c - '0';
    }
    return neg?-x:x;
}
main() {
	int N, a, b;
	while(N = readint()) {
		for(a = 0; a < N; a++)
        	Ki[a] = readint();
        MergeSort(0, N-1);
        if(N == 1) {puts("Yes");continue;}
        int D = (Ki[N-1]-Ki[0])/(N-1); 
        if(D == 0) {puts("Yes");continue;} 
        for(a = 1; a < N; a++) 
            if(Ki[a] != Ki[a-1]+D) break;
        puts((a == N) ? "Yes" : "No"); 
	} 
    return 0; 
}
