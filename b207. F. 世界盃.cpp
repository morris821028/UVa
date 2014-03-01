#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Data {
	char name[101];
	int inball, outball, score;
}Data;
Data team[8];
int cmp(const void *a, const void *b) {
	Data *aa, *bb;
	aa = (Data *)a, bb = (Data *)b;
	if(aa->score > bb->score)	return 0;
	else if(aa -> score < bb->score)	return 1;
	else {
		if(aa->inball > bb->inball)	return 0;
		else if(aa->inball < bb->inball) return 1;
		else {
			if(aa->outball < bb->outball)	return 0;
			else if(aa->outball > bb->outball) return 1;
			else {
				int i;
				for(i = 0; ; i++)
					if(aa->name[i] < bb->name[i])
						return 0;
					else if(aa->name[i] > bb->name[i])
						return 1;
				return 0;
			}
		}
	}
}
main() {
	int n, a, b, As, Bs;
	scanf("%d", &n);
	while(n--) {
		for(a = 0; a < 8; a++) {
			scanf("%s", team[a].name);
			team[a].inball = 0, team[a].outball = 0;
			team[a].score = 0;
		}
		char A[101], B[101], Aidx, Bidx;
		for(a = 0; a < 12; a++) {
			scanf("%s %d %d %s", A, &As, &Bs, B);
			for(b = 0; b < 8; b++)
				if(!strcmp(team[b].name, A))
					{Aidx = b;break;}
			for(b = 0; b < 8; b++)
				if(!strcmp(team[b].name, B))
					{Bidx = b;break;}
			team[Aidx].inball += As, team[Aidx].outball += Bs;
			team[Bidx].inball += Bs, team[Bidx].outball += As;
			if(As > Bs)	team[Aidx].score += 3;
			else if(As < Bs) team[Bidx].score += 3;
			else	team[Aidx].score++, team[Bidx].score++;
		}
		qsort(team, 4, sizeof(Data), cmp);
		qsort(team+4, 4, sizeof(Data), cmp);
		for(a = 0; a < 2; a++)
			printf("A%d %s\n", a+1, team[a].name);
		for(a = 4; a < 6; a++)
			printf("B%d %s\n", a-3, team[a].name);
		if(!cmp(&team[2], &team[6]))
			printf("BEST3 %s\n", team[2].name);
		else	printf("BEST3 %s\n", team[6].name);
	}
	return 0;
}
