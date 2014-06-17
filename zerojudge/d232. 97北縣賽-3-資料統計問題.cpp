#include<stdio.h>
#include<string.h>
void Merge(int, int, int);
void MergeSort(int, int);
char name[101][21], s[20], FM[2], book[2];
int custyr[101] = {}, custmy[101] = {};
int Data[101], X[101];
main() {
	int n;
	while(scanf("%d", &n) == 1) {
		int map[10][10] = {}, tpbook[27] = {};
		int yr, my, a, b, c, namet = 0, Idx;
		memset(custmy, 0, sizeof(custmy));
		for(a = 0; a < n; a++) {
			scanf("%s %s %s %d %d", s, FM, book, &yr, &my);
			for(b = 0; b < namet; b++)
				if(!strcmp(name[b], s))
					break;
			if(b == namet)	namet++, strcpy(name[b], s);
			Idx = b;
			custyr[Idx] = yr, custmy[Idx] += my;
			tpbook[book[0]-'A'] += my;
		}
		int max = 0, maxv, x, y;
		for(a = 0; a < 26; a++)
			if(tpbook[a] > max)
				max = tpbook[a], maxv = a;
		printf("%c\n", maxv+'A');
		for(a = 0; a < namet; a++) {
			x = (custyr[a]-1)/10, y = (custmy[a]-1)/1000;
			map[y][x] ++;
		}
		for(a = 0; a < 10; a++) {
			for(b = 0; b < 10; b++)
				printf("%d ", map[a][b]);
			puts("");
		}
		for(a = 0; a < namet; a++)	Data[a] = a;
		MergeSort(0, namet-1);
		int i = namet > 5 ? 4 : namet-1, j = custmy[Data[i]];
		for(a = 0; a < namet; a++)
			if(custmy[Data[a]] >= j)
				printf("%s %d\n", name[Data[a]], custmy[Data[a]]);
	}
	return 0;
}
int cmp(int x, int y) {
	if(custmy[x] > custmy[y])
		return 1;
	else if(custmy[x] < custmy[y])
		return 0;
	else {
		int a;
		for(a = 0; ; a++)
			if(name[x][a] < name[y][a])
				return 1;
			else if(name[x][a] > name[y][a])
				return 0;
		return 1;
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
