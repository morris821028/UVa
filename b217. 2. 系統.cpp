#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	char Subject[1025];
	int Date[4];
	int ID[100], IDl;
	int input;
}Article;
Article in[10000];
int cmp(const void *a, const void *b) {
	Article *aa, *bb;
	aa = (Article *)a, bb = (Article *)b;
	
	if(aa->Date[3] > bb->Date[3])	return 1;
	else if(aa->Date[3] < bb->Date[3])	return 0;
	else {
		if(aa->Date[0] > bb->Date[0])	return 1;
		else if(aa->Date[0] < bb->Date[0])	return 0;
		else {
			if(aa->Date[1] > bb->Date[1])	return 1;
			else if(aa->Date[1] < bb->Date[1])	return 0;
			else {
				if(aa->Date[2] > bb->Date[2])	return 1;
				else if(aa->Date[2] < bb->Date[2])	return 0;
				else {
					return aa->input > bb->input;
				}
			}
		}
	}
}
main() {
	char Subject[10], Date[10], ID[10], name[1025];
	int M, D, H, Y, id, index = 0, a, b, C = 0;
	while(scanf("%s", Subject) == 1) {
		++C;
		getchar(), gets(name);
		scanf("%s %d %d %d %d", Date, &M, &D, &H, &Y);
		scanf("%s %d", ID, &id);
		int i = 0, j = 0, l = strlen(name);
		if(name[0] == 'R' && (name[1] == 'E' || name[1] == 'e')&& name[2] == ':')
			i = 3;
		while(name[i] == ' ')	i++;
		for(; i < l; i++)	name[j++] = name[i];
		i = j-1;
		while(name[i] == ' ')	i--;
		name[i+1] = '\0';
		for(a = 0; a < index; a++) {
			if(!strcmp(in[a].Subject, name)) {
				in[a].ID[in[a].IDl++] = id;
				break;
			}
		}
		if(a == index) {
			for(b = 0; name[b]; b++)
				in[a].Subject[b] = name[b];
			in[a].Subject[b] = '\0';
			in[a].Date[0] = M, in[a].Date[1] = D, in[a].Date[2] = H, in[a].Date[3] = Y;
			in[a].IDl = 0, in[a].ID[in[a].IDl++] = id;
			in[a].input = C;
			index++;
			if(index > 3) {
				for(b = 0; b < index-1; b++)
					if(cmp(&in[b], &in[index-1]) == 1) {
						break;
					}
				if(b != index-1)
					in[b] = in[index-1];
				index--;
			}
		}
	}
	qsort(in, index, sizeof(Article), cmp);
	for(a = 0; a < 2; a++) {
		printf("Subject: %s\nID: ", in[a].Subject);
		for(b = 0; b < in[a].IDl; b++)
			if(b == 0)	printf("%d", in[a].ID[b]);
			else printf(",%d", in[a].ID[b]);
		puts("");
	}
	return 0;
}
