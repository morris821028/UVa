#include<stdio.h>
#include<stdlib.h>
#include<string.h>	
char child[40], parent[40];
char people1[40], people2[40];
char recode[301][40], map[301][301];
int rt = 0, i, j;
int find_recode(char *s) {
	int i, Idx = -1;
	for(i = 0; i < rt; i++)
		if(!strcmp(recode[i], s)) {
			Idx = i;break;
		}
	if(i == rt)
		strcpy(recode[rt], s), Idx = rt, ++rt;
	return Idx;
}
int min(int x, int y) {
	return x < y ? x : y;
}
void Print(int i, int j) {
	int t;	
	if(i == 1 && j == 1) {
		puts("sibling");
		return;
	}
	if(i == 0) {
		for(t = 2; t < j; t++)
			printf("great ");
		if(j >= 2)	
			printf("grand ");
		puts("parent");
		return;
	}
	if(j == 0) {
		for(t = 2; t < i; t++)
			printf("great ");
		if(i >= 2)
			printf("grand ");
		puts("child");
		return;
	}
	int k = min(i-1, j-1), jj = abs(i-j);
	printf("%d cousin", k);
	if(jj)
		printf(" removed %d", jj);
	puts("");
}
void Judge(char *x, char *y) {
	int p1, p2, find;
	p1 = find_recode(x);
	p2 = find_recode(y);
	if(p1 == p2) {
		puts("no relation");
		return;
	}
	int path1[300], path2[300], p1Idx, p2Idx;
	p1Idx = 0, p2Idx = 0;
	path1[0] = p1, path2[0] = p2;
	while(1) {
		find = 0;
		for(i = 0; i < rt; i++) {
			if(map[path1[p1Idx]][i]) {
				path1[++p1Idx] = i;
				find = 1;
				break;
			}
		}
		if(!find)	break;
	}
	while(1) {
		find = 0;
		for(i = 0; i < rt; i++) {
			if(map[path2[p2Idx]][i]) {
				path2[++p2Idx] = i;
				find = 1;
				break;
			}
		}
		if(!find)	break;
	}
	for(i = 0; i <= p1Idx; i++)
		for(j = 0; j <= p2Idx; j++)
			if(path1[i] == path2[j]) {
				Print(i, j);
				return;
			}
	puts("no relation");
}
int main() {
	memset(map, 0, sizeof(map));
	while(scanf("%s %s", child, parent) == 2) {
		if(!strcmp(child, "no.child") && !strcmp(parent, "no.parent"))
			break;
		int chIdx, paIdx;
		chIdx = find_recode(child);
		paIdx = find_recode(parent);
		map[chIdx][paIdx] = 1;
	}
	int C = 1;
	while(scanf("%s %s", people1, people2) == 2) {
		Judge(people1, people2);
	}
	return 0;
}
