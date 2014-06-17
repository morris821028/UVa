#include<stdio.h>
typedef struct {
	int t;
}Data;
Data X[50000];
void Merge(int l, int m, int h, Data A[]) {
    int In1 = l, In2 = m+1;
    int a, b, Top = 0;
    while(In1 <= m && In2 <= h) 
        if((A[In1].t < A[In2].t))
             X[Top++] = A[In1++];
       else  X[Top++] = A[In2++];
    while(In1 <= m)   X[Top++] = A[In1++];
    while(In2 <= h)   X[Top++] = A[In2++];
    for(a=0,b=l;a<Top;a++,b++) 
        A[b]=X[a];
} 
void MergeSort(int l, int h, Data A[]) {
    if(l < h) {
        int m = (l+h)/2;
        MergeSort(l  , m, A);
        MergeSort(m+1, h, A);
        Merge(l, m, h, A); 
    }
}
main() {
	int t, n, m, a;
	Data A[50000], B[50000];
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		for(a = 0; a < n; a++)	scanf("%d", &A[a].t);
		for(a = 0; a < m; a++)	scanf("%d", &B[a].t);
		MergeSort(0, n-1, A);
		MergeSort(0, m-1, B);
		int in1 = 0, in2 = 0, Ans = 0;
		for(; in1 < n && in2 < m; in2++) {
			if(A[in1].t <= B[in2].t)
				Ans++, in1++;
		}
		if(Ans)	printf("%d\n", Ans);
		else puts("Santa Claus wishes you get AC in the next submission.");
	}
	return 0;
}
