#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <map>
using namespace std;
map<string, int> R;
int getLabel(string s) {
	int &x = R[s];
	return x == 0 ? x = R.size() : x;
}

#define MAXN 4096
int main() {
	int Nm, Ni, Nc, n, x, y;
	char s[MAXN];
	while(scanf("%d %d %d %d", &Nm, &Ni, &Nc, &n) == 4) {
		if(Nm + Ni + Nc + n == 0)
			break;
		R.clear();
		int Icnt[MAXN] = {}, Ccnt[MAXN] = {}, g[MAXN] = {};
		int eflag = 0;
		for(int i = 1; i < MAXN; i++)
			g[i] = i;
		for(int i = 0; i < Nm; i++) {
			scanf("%s", s);
			x = getLabel(s);
			scanf("%s", s);
			y = getLabel(s);
			if(g[x] != x && g[x] != y)	eflag = 1;
			g[x] = y;
		}
		for(int i = 0; i < Ni; i++) {
			scanf("%s %d", s, &y);
			x = getLabel(s);
			Icnt[x] = y;
		}
		for(int i = 0; i < Nc; i++) {
			scanf("%s %d", s, &y);
			x = getLabel(s);
			Ccnt[x] = y;
		}
		if(eflag) {
			puts("Protein mutations are not deterministic");
			continue;
		}
		eflag = 1;
		for(int i = 0; i <= n; i++) {			
			if(memcmp(Icnt, Ccnt, sizeof(Icnt)) == 0) {
				printf("Cure found in %d mutation(s)\n", i);
				eflag = 0;
				break;
			}
			int next[MAXN] = {};
			for(int j = 1; j <= R.size(); j++) {
				next[g[j]] += Icnt[j];
			}
			memcpy(Icnt, next, sizeof(next));
		}
		if(eflag)
			puts("Nostalgia for Infinity is doomed");
	}
	return 0;
}
