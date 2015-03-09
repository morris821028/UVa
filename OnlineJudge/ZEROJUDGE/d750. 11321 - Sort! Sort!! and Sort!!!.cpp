#include<stdio.h>
#include<stdlib.h>
int Data[10000], X[10000], n, m, a;
int cmp(int x, int y) {
	int tx = x%m, ty = y%m;
	if((x&1) && (!(y&1))) {
		if(tx == ty)	return 1;
		return tx < ty;
	}
	if((!(x&1)) && (y&1)) { 
		if(tx == ty)	return 0;
		return tx < ty;
	}
	if((x&1) && (y&1)) {
		if(tx == ty) {
			if(x > y)	return 1;
			else		return 0;
		}
		else return tx < ty;
	}
	else {
		if(tx == ty) {
			if(x < y)	return 1;
			else		return 0;
		}
		else return tx < ty;
	}
}
void Merge(int l, int m, int h) {
	int In1 = l, In2 = m+1;
	int a, b, Top = 0;
	while(In1 <= m && In2 <= h)
		if(cmp(Data[In1], Data[In2]))
			X[Top++] = Data[In1++];
		else X[Top++] = Data[In2++];
	while(In1 <= m)	X[Top++] = Data[In1++];
	while(In2 <= h) X[Top++] = Data[In2++];
	for(a = 0, b = l; a < Top; a++, b++)
		Data[b] = X[a]; 
}
void MergeSort(int l, int h) {
	if(l < h) {
		int m = (l+h)/2;
		MergeSort(l, m);
		MergeSort(m+1, h);
		Merge(l, m, h); 
	}
}
main() {
	printf("%d\n", (-100)%3);
	while(scanf("%d %d", &n, &m) == 2) {
		for(a = 0; a < n; a++)
			scanf("%d", &Data[a]);
		MergeSort(0, n-1);
		printf("%d %d\n", n, m);
		for(a = 0; a < n; a++)
			printf("%d\n", Data[a]);
	}
	return 0;
}
