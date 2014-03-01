#include<stdio.h>
#include<stdlib.h>
#define oo 2147483647
int cmp(const void *i, const void *j) {
	return *(int *)i - *(int *)j;
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
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
	int t, n, X[1001], Y[1001], i;
	ReadInt(&t);
	while(t--) {
		ReadInt(&n);
		int sumx = 0, sumy = 0;
		for(i = 0; i < n; i++) {
			ReadInt(&X[i]), ReadInt(&Y[i]);
			sumx += X[i];
			sumy += Y[i];
		}
		qsort(X, n, sizeof(int), cmp);
		qsort(Y, n, sizeof(int), cmp);
		sumx -= X[0]*n, sumy -= Y[0]*n;
		int Ans1 = 1, Ans2 = 1, minx = sumx, miny = sumy;
		for(i = 1; i < n; i++) {
			sumx = sumx + (X[i] - X[i-1])*(2*i-n);
			if(sumx == minx)
				Ans1 += X[i] - X[i-1];
			else if(sumx < minx)
				minx = sumx, Ans1 = 1;
		}
		for(i = 1; i < n; i++) {
			sumy = sumy + (Y[i] - Y[i-1])*(2*i-n);
			if(sumy == miny)
				Ans2 += Y[i] - Y[i-1];
			else if(sumy < miny)
				miny = sumy, Ans2 = 1;
		}
		printf("%d %d\n", minx + miny, Ans1*Ans2);
	}
	return 0;
}
