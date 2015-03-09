#include<stdio.h>
#include<string.h>
struct {
	char book[101], name[31];
	int n;
}Data[100], X[100];
char ASCII[256];
char sort[] = "XOBCDAFGHUJKLMNIPQRSTEVWYZ";
int compare(int In1, int In2) {
	int a, flag = 0;
	for(a = 0; ; a++) {
		if(ASCII[Data[In1].name[a]] < ASCII[Data[In2].name[a]])
			return 1;
		else if(ASCII[Data[In1].name[a]] > ASCII[Data[In2].name[a]])
			return 0;
		if(Data[In1].name[a] == Data[In2].name[a] && Data[In1].name[a] == '\0') break;
	}
	if(Data[In1].n < Data[In2].n) return 1;
	else if(Data[In1].n > Data[In2].n) return 0;
	for(a = 0; ; a++) {
		if(ASCII[Data[In1].book[a]] < ASCII[Data[In2].book[a]])
			return 1;
		else if(ASCII[Data[In1].book[a]] > ASCII[Data[In2].book[a]])
			return 0;
	}
}
void Merge(int l, int m, int h) {
	int In1 = l, In2 = m+1;
	int a, b, Top = 0;
	while(In1 <= m && In2 <= h) {
		if(compare(In1, In2) == 1) {
			X[Top++] = Data[In1++];
		}
		else {
			X[Top++] = Data[In2++];
		}
	}
	while(In1 <= m) X[Top++] = Data[In1++];
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
	int n, a, b, t;
	char s[201];
	for(a = 0; a < 26; a++)
		ASCII[sort[a]] = a;
	for(a = 0; a < 26; a++)
		ASCII[sort[a]-'A'+'a'] = a;
	while(scanf("%d", &n) == 1) {
		getchar();
		for(a = 0; a < n; a++) {
			gets(s);
			for(b = 0, t = 0; s[b]; b++) {
				if(s[b] == ',') {b+=2;break;}
				Data[a].name[t++] = s[b];
			}
			Data[a].name[t] = '\0';
			for(t = 0; s[b]; b++) {
				if(s[b] == '(') {b++;break;}
				Data[a].book[t++] = s[b];
			}
			Data[a].book[t-1] = '\0';
			for(t = 0; s[b]; b++) {
				if(s[b] <= '9' && s[b] >= '0')
					t = t*10 + s[b]-'0';
			}
			Data[a].n = t;
		}
		MergeSort(0, n-1);
		for(a = 0; a < n; a++) {
			printf("%s, %s (%d)\n", Data[a].name, Data[a].book, Data[a].n);
		}
	}
	return 0;
}
