#include<stdio.h>
#include<stdlib.h>
typedef struct {
	char name[2];
	int id, h;
}D;
D Data[6], X[6];
int cmp1(D A, D B) {
	return A.id < B.id;
}
int cmp2(D A, D B) {
	return A.h < B.h || (A.h == B.h && A.id < B.id);
}
void Merge(int l, int m, int h, int cmp(D, D)) {
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
void MergeSort(int l, int h, int cmp(D, D)) {
	if(l < h) {
		int m = (l+h)/2;
		MergeSort(l, m, cmp);
		MergeSort(m+1, h, cmp);
		Merge(l, m, h, cmp); 
	}
}
main() {
	int m, n, a;
	int Ans[7] = {0, 1, 0, 5, 4, 3, 2};
	int ( *Function[2])(D, D) = {cmp2, cmp1};
	while(scanf("%d %d", &m, &n) == 2) {
		for(a = 0; a < 6; a++)
			scanf("%s %d %d", Data[a].name, &Data[a].id, &Data[a].h);
		MergeSort(0, 5,( *Function[m&1]));
		printf("%s\n", Data[Ans[n]].name);
	}
	return 0;
}
