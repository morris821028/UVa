#include <stdio.h> 
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

int usedg[16][16][16][16][5];
long long dp[16][16][16][16][5];
double dp2[16][16][16][16][5];
const long long MAXVAL = 1e+18 + 10;
long long g(int f4, int f3, int f2, int f1, int last) {
	if (usedg[f4][f3][f2][f1][last])
		return dp[f4][f3][f2][f1][last];
	usedg[f4][f3][f2][f1][last] = 1; 
	long long &ret = dp[f4][f3][f2][f1][last];
	double &ret2 = dp2[f4][f3][f2][f1][last];
	if (f4 + f3 + f2 + f1 == 0) {
		ret = 1;
		ret2 = 1;
		return 1;
	}
	if (f4 > 0) {
		ret += 4 * f4 * g(f4-1, f3+1, f2, f1, 4);
		ret2 += 4 * f4 * dp2[f4-1][f3+1][f2][f1][4];
	}
	ret = min(ret, MAXVAL);
	if (ret2 > MAXVAL)	return ret;
	if (f3 > 0) {
		if (last == 4) {
			ret += 3 * (f3 - 1) * g(f4, f3-1, f2+1, f1, 3);
			ret2 += 3 * (f3 - 1) * dp2[f4][f3-1][f2+1][f1][3];
		} else {
			ret += 3 * (f3) * g(f4, f3-1, f2+1, f1, 3);
			ret2 += 3 * (f3) * dp2[f4][f3-1][f2+1][f1][3];
		}
	}
	ret = min(ret, MAXVAL);
	if (ret2 > MAXVAL)	return ret;
	if (f2 > 0) {
		if (last == 3) {
			ret += 2 * (f2 - 1) * g(f4, f3, f2-1, f1+1, 2);
			ret2 += 2 * (f2 - 1) * dp2[f4][f3][f2-1][f1+1][2];
		} else {
			ret += 2 * (f2) * g(f4, f3, f2-1, f1+1, 2);
			ret2 += 2 * (f2) * dp2[f4][f3][f2-1][f1+1][2];
		}
	}
	ret = min(ret, MAXVAL);
	if (ret2 > MAXVAL)	return ret;
	if (f1 > 0) {
		if (last == 2) {
			ret += (f1 - 1) * g(f4, f3, f2, f1-1, 1);
			ret2 += (f1 - 1) * dp2[f4][f3][f2][f1-1][1];
		} else {
			ret += f1 * g(f4, f3, f2, f1-1, 1);
			ret2 += f1 * dp2[f4][f3][f2][f1-1][1];
		}
	}
	ret = min(ret, MAXVAL);
	if (ret2 > MAXVAL)	return ret;
	return ret;
}

int card2Num(char suit, char rank) {
	int s, r;
	switch(suit) {
		case 'S': s = 3;break;
		case 'C': s = 0;break;
		case 'H': s = 2;break;
		case 'D': s = 1;break;
	}
	switch(rank) {
		case '2'...'9': r = rank-'0'-2;break;
		case 'T': r = 12;break;
		case 'J': r = 9;break;
		case 'Q': r = 11;break;
		case 'K': r = 10;break;
		case 'A': r = 8;break;
	}
	return r * 4 + s;
}
int main() {
	int cases = 0;
	int N;
	long long K;
	char psuit[] = "CDHS", prank[] = "23456789AJKQT";
	while (scanf("%d %lld", &N, &K) == 2) {
		if (N == 0 && K == 0)
			break;
		char card[10];
		int A[64];
		for (int i = 0; i < N; i++) {
			scanf("%s", card);
			int x = card2Num(card[1], card[0]);
			A[i] = x;
		}
		printf("Case %d:", ++cases);
		int ret[64];
		int NOT_FOUND = 0; 
		K--;
		for (int i = 0; i < N; i++) {
			sort(A+i, A+N);
			ret[i] = -1;
			for (int j = i; j < N; j++) {
				int ch = A[j];
				int cnt[13] = {}, f[8] = {};
				if (i && ch/4 == ret[i-1]/4) 
					continue;
				for (int k = i; k < N; k++)
					cnt[A[k]/4]++;
				int last = cnt[ch/4]--;
				for (int k = 0; k < 13; k++)
					f[cnt[k]]++;
				long long way = g(f[4], f[3], f[2], f[1], last);			
//				printf("%d %d %d %d - %d %lld\n", f[4], f[3], f[2], f[1], last, way);
//				printf("%lld %lf\n", way, dp2[f[4]][f[3]][f[2]][f[1]][last]);
				if (dp2[f[4]][f[3]][f[2]][f[1]][last] > K) {
					swap(A[i], A[j]);
					ret[i] = ch;
					break;
				} else {
					K -= way;
				}
			}
			if (ret[i] == -1) {
				NOT_FOUND = 1;
				break;
			}
//			puts("------");
		}
		if (NOT_FOUND) {
			puts(" Not found");
			continue;
		}
		for (int i = 0; i < N; i++)  {
//			printf("%d\n", ret[i]);
			printf(" %c%c", prank[ret[i]/4], psuit[ret[i]%4]);
		}
		puts("");
	}
	return 0;
}
/*
50 1
2C 2D 2H 2S
3C 3D 3H 3S
4C 4D 4H 4S
5C 5D 5H 5S
6C 6D 6H 6S
7C 7D 7H 7S
8C 8D 8H 8S
9C 9D 9H 9S
TC TD TH TS
JC JD JH JS
QC QD QH QS
KC KD KH
AC AD AH
*/
