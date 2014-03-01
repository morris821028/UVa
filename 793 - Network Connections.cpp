#include<stdio.h>
int Parent[1001], Rank[1001];
void MakeInit(int n) {
	int i;
	for(i = 0; i <= n; i++)
		Parent[i] = i, Rank[i] = 1;
}
int FindParent(int x) {
	if(Parent[x] != x)
		Parent[x] = FindParent(Parent[x]);
	return Parent[x];
}
void Link(int x, int y) {
	if(Rank[x] > Rank[y]) {
		Rank[x] += Rank[y];
		Parent[y] = x;
	} else {
		Rank[y] += Rank[x];
		Parent[x] = y;
	}
}
void Union(int x, int y) {
	x = FindParent(x), y = FindParent(y);
	if(x != y)
		Link(x, y);
}
int CheckLink(int x, int y) {
	x = FindParent(x), y = FindParent(y);
	if(x != y)
		return 0;
	else
		return 1;
}
int main() {
	int T, N, x, y;
	char s[100], ss[2];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		MakeInit(N);
		getchar();
		int yes = 0, no = 0;
		while(gets(s)) {
			if(s[0] == '\0')	break;
			sscanf(s, "%s %d %d", ss, &x, &y);
			if(ss[0] == 'c')
				Union(x, y);
			else {
				if(CheckLink(x, y))
					yes++;
				else
					no++;
			}
		}
		printf("%d,%d\n", yes, no);
		if(T)	puts("");
	}
    return 0;
}
