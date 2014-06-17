#include<stdio.h>
#include<string.h>
int main() {
	char s[101], sx[101], sy[101], D[201][20];
	int map[201][201], mt[201], size;
	int n, i, j, k, fx, fy;
	scanf("%d", &n);
	getchar();
	gets(s);
	while(n--) {
		size = 0;
		while(gets(s)) {
			if(s[0] == '*')	break;
			strcpy(D[size], s);
			size++;
		} 
		memset(mt, 0, sizeof(mt));
		for(i = 0; i < size; i++) {
			for(j = 0; j < size; j++) {
				int dif = 0;
				for(k = 0; D[i][k] && D[j][k]; k++)
					if(D[i][k] != D[j][k])
						dif++;
				if(D[i][k] == 0 && D[j][k] == 0 && dif == 1)
					map[i][mt[i]++] = j, map[j][mt[j]++] = i;
			}
		}
		while(gets(s)) {
			if(s[0] == '\0')	break;
			sscanf(s, "%s %s", sx, sy);
			for(i = 0; i < size; i++)
				if(!strcmp(sx, D[i])) {
					fx = i;break;
				}
			for(i = 0; i < size; i++)
				if(!strcmp(sy, D[i])) {
					fy = i;break;
				}
			printf("%s %s ", sx, sy);
			if(fx == fy)	puts("0");
			else {
				int Used[size], Q[size*size], Qt = -1, V[size], tn;
				memset(Used, 0, sizeof(Used));
				Q[++Qt] = fx, V[fx] = 0, Used[fx] = 1;
				for(i = 0; i <= Qt; i++) {
					tn = Q[i];
					if(tn == fy)	break;
					for(j = 0; j < mt[tn]; j++)
						if(Used[map[tn][j]] == 0) {
							Used[map[tn][j]] = 1, V[map[tn][j]] = V[tn]+1;
							Q[++Qt] = map[tn][j];
						}
				}
				printf("%d\n", V[fy]);
			}
		}
		if(n)	puts("");
	}
    return 0;
}
