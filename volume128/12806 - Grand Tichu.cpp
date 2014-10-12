#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
long long C[50][50];
const char kind[20] = "ADPMd23456789TJQK";
int ihand[20], ohand[20], mhand[20];
int suffix[20];
long long va[10], vb;
void dfs(int idx, int card, long long ways) {
	if (idx > 4) {
		ways = ways * C[suffix[idx]][14 - card];
		int hh = 0;
		if (ohand[1] > 0 && ohand[2] > 0 && ohand[0] > 0)
			hh = 1, va[hh] += ways;// D P A
		if (ohand[1] > 0 && ohand[0] >= 2)
			hh = 2, va[hh] += ways;// D A A
		if (ohand[2] > 0 && ohand[0] >= 3)
			hh = 3, va[hh] += ways; // P A A A
		if (ohand[1] > 0 && ohand[2] > 0 && ohand[3] > 0 && ohand[4] > 0)
			hh = 4, va[hh] += ways; // D P M d
		vb += ways;
		return ;
	}
	if (card == 14) {
		int hh = 0;
		if (ohand[1] > 0 && ohand[2] > 0 && ohand[0] > 0)
			hh = 1, va[hh] += ways;// D P A
		if (ohand[1] > 0 && ohand[0] >= 2)
			hh = 2, va[hh] += ways;// D A A
		if (ohand[2] > 0 && ohand[0] >= 3)
			hh = 3, va[hh] += ways; // P A A A
		if (ohand[1] > 0 && ohand[2] > 0 && ohand[3] > 0 && ohand[4] > 0)
			hh = 4, va[hh] += ways; // D P M d
		vb += ways;
		return ;
	}
	if (idx == 17 || card + suffix[idx] < 14)	return ;
	for (int i = 0; i <= ihand[idx] && card + i <= 14; i++) {
		ohand[idx] += i;
		dfs(idx+1, card + i, ways * C[ihand[idx]][i]);
		ohand[idx] -= i;
	}
}
int main() {
	for (int i = 0; i < 50; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
	char hand[64];
	while (scanf("%s", &hand) == 1 && hand[0] != '0') {
		memset(ihand, 0, sizeof(ihand));
		memset(ohand, 0, sizeof(ohand));
		for (int i = 4; i < 17; i++)
			ihand[i] = 4, mhand[i] = 4;
		ihand[0] = 4, mhand[0] = 4;
		for (int i = 1; i <= 4; i++)
			ihand[i] = 1, mhand[i] = 1;
		for (int i = 0; i < 8; i++) {
			int p = find(kind, kind + 17, hand[i]) - kind;
			ihand[p]--, ohand[p]++;
		}
		memset(suffix, 0, sizeof(suffix));
		for (int i = 17; i >= 0; i--)
			suffix[i] = suffix[i+1] + ihand[i];
		memset(va, 0, sizeof(va));
		vb = 0;
		dfs(0, 8, 1);
		int ok = 0;
		for (int i = 0; i < 4; i++) {
			double p = (double)va[i] / vb;
			if (p > 0.25)	ok = 1;
		}
		if (ok)
			puts("Grand Tichu!");
		else
			puts("...");
	}
	return 0;
}
/*
D23468AA
D2P4688K
D23468KA
D2233889
PdM2345T
PdM234AA
0

D23468AA
0.000000
0.125000
1.000000
0.025439
Grand Tichu
D2P4688K
0.000000
0.424761
0.070768
0.004394
Grand Tichu
D23468KA
0.000000
0.125000
0.336263
0.003315
Grand Tichu
D2233889
0.000000
0.046558
0.070768
0.000298
...
PdM2345T
0.000000
0.046558
0.006332
0.004394
...
PdM234AA
0.000000
0.125000
0.125000
0.236702
...
*/
