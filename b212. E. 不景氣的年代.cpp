#include<stdio.h>
#include<string.h>
typedef struct {
	int a, b, c;
}INF;
INF A[5000], B[5000], X[5000];
void Merge(int l, int m, int h,INF Data[]) {
    int In1 = l, In2 = m+1;
    int a, b, Top = 0;
    while(In1 <= m && In2 <= h) 
        if(Data[In1].a < Data[In2].a 
		|| (Data[In1].a == Data[In2].a && Data[In1].b < Data[In2].b))
             X[Top++] = Data[In1++];
       else  X[Top++] = Data[In2++];
    while(In1 <= m)   X[Top++] = Data[In1++];
    while(In2 <= h)   X[Top++] = Data[In2++];
    for(a = 0, b = l; a < Top; a++, b++) 
        Data[b] = X[a];
}
void MergeSort(int l, int h, INF Data[]) {
	if(l < h) {
        int m=(l+h)/2;
        MergeSort(l  ,m, Data);
        MergeSort(m+1,h, Data);
        Merge(l, m, h, Data); 
    }
}
int C[10002] = {}, LOW[10002];
int Modify (int N, int L) {
    while(N <= L) {
        C[N] += 1;
        N += LOW[N];
    }
}
int Operator (int N) {
    int Sum = 0;
    while(N) {
        Sum += C[N];
        N -= LOW[N];
    }
    return Sum;
}
main() {
	int k, n, a, b;
	for(a = 0; a < 10002; a++)	LOW[a] = a & (-a);
	scanf("%d", &k);
	while(k--) {
		scanf("%d", &n);
		for(a = 0; a < n; a++)
			scanf("%d %d %d", &A[a].a, &A[a].b, &A[a].c), 
			B[a].a = A[a].b, B[a].b = A[a].a, B[a].c = A[a].c;
		MergeSort(0, n-1, A), MergeSort(0, n-1, B);
		int Pa, Pb, Pc, t, Ans = 0;
		for(a = 0; a < n; ) {
			Pa = A[a].a;
			while(a < n && A[a].a <= Pa)	a++;
			memset(C, 0, (10000-Pa+2)*4);
			for(b = 0; b < n && Pa+B[b].a <= 10000; ) {
				Pb = B[b].a, Pc = 10000-Pa-Pb+1;
				while(b < n && B[b].a <= Pb) {
					if(B[b].b <= Pa)	Modify(B[b].c+1, Pc);
					b++;
				}
				t = Operator(Pc);
				Ans = Ans > t ? Ans : t;
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}
