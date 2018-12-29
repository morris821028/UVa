#include <bits/stdc++.h>
using namespace std;

const int fXCap = 48, sXCap = 64;
int read(int p[]) {
	return scanf("%d %d %d %d %d %d", &p[0], &p[1], &p[2], &p[3], &p[4], &p[5]) == 6;
}

int round_wagon(int n, int cap) {
	return n / cap + (n % cap != 0);
}

int satify(int p[], int sa, int sb) {
	int f = round_wagon(p[0], fXCap) + round_wagon(p[1], fXCap);
	int s = round_wagon(p[2], sXCap) + round_wagon(p[3], sXCap);
	if (sa < f)
		return 0;
	if (sb < s)
		return 0;
	if (sb * sXCap - p[2] - p[3] < p[4])
		return 0;
	if ((sa * fXCap - p[0] - p[1]) + (sb * sXCap - p[2] - p[3] - p[4]) < p[5])
		return 0;
	return 1;
}
void compute_pba(int p[], int q[], int &fX, int &sX) {
	int a, b, c, d;
	for (int sum = 0; sum <= 200; sum++) {
		for (int i = 0; i <= sum; i++) {
			if (satify(p, i, sum-i) && satify(q, i, sum-i)) {
				fX = i, sX = sum-i;
				return;
			}
		}
	}
}
int main() {
	int pa[6], pb[6], ba[6];
	int cases = 0;
	while (read(pa)) {
		read(pb), read(ba);
		int fX = 0, sX = 0;
		for (int i = 0; i < 6; i++)
			pb[i] += pa[i], ba[i] += pa[i];
		compute_pba(pb, ba, fX, sX);
		if (cases++)
			puts("");
		printf("%d\n%d\n", fX, sX);
	}
	return 0;
}
/*
20 120 50 80 100 30
40 80 5 10 100 40
15 12 20 100 30 20

20 120 50 80 100 30
0 0 0 0 0 0
0 0 0 0 0 0

0 0 0 0 0 0
40 80 5 10 100 40
15 12 20 100 30 20

*/
