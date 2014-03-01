#include <stdio.h>
#include<time.h>
void MergeSort(int, int);
void Merge(int, int, int);
int Data[10000001], X[10000001];
int main() {
	freopen("in1.txt", "rt", stdin);   
	freopen("out3.txt", "w+t", stdout);
    clock_t st, ed;
    st = clock();
	int n = 0;
	while(scanf("%d", &Data[n]) == 1) n++;
	MergeSort(0, n-1);
	/*
	for(i = 0; i < n; i++)
		printf("%d ", numbers[i]);*/
	ed = clock();
	printf("%f\n", (float)(ed - st )/CLOCKS_PER_SEC);
	return 0;
}
void MergeSort(int l, int h) {
    if(l < h) {
        int m = (l+h)/2;
        MergeSort(l, m);
        MergeSort(m+1, h);
        Merge(l, m, h);
    }
}
void Merge(int l, int m, int h) {
    int In1 = l, In2 = m+1;
    int a, b, Top = 0;
    while(In1 <= m && In2 <= h) {
        if(Data[In1] < Data[In2])
            X[Top++] = Data[In1++];
        else
            X[Top++] = Data[In2++];
    }
    while(In1 <= m) X[Top++] = Data[In1++];
    while(In2 <= h)    X[Top++] = Data[In2++];
    for(a = 0, b = l; a < Top; a++, b++)
        Data[b] = X[a];
}
