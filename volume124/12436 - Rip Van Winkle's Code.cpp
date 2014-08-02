#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXN 262144
#define MAXM 1048576 + 10 
typedef long long LL;
LL sum[MAXM];
LL preB[MAXM], preD[MAXM]; // base, diff
LL sufB[MAXM], sufD[MAXM];
LL setB[MAXM], setD[MAXM];

void pushUp(int k) {
	sum[k] = sum[k<<1] + sum[k<<1|1];
}
void pushDown(int k, int l, int r) {
	int m = (l + r) /2;
	
	if(setB[k]) {
		setB[k<<1] = 1, setD[k<<1] = setD[k];
		setB[k<<1|1] = 1, setD[k<<1|1] = setD[k];
		preB[k<<1] = preD[k<<1] = sufB[k<<1] = sufD[k<<1] = 0;
		preB[k<<1|1] = preD[k<<1|1] = sufB[k<<1|1] = sufD[k<<1|1] = 0;
		sum[k<<1] = (m - l + 1) * setD[k];
		sum[k<<1|1] = (r - m) * setD[k];
		setB[k] = setD[k] = 0;
	}
	if(preB[k]) {
		preB[k<<1] += preB[k], preD[k<<1] += preD[k];
		preB[k<<1|1] += preB[k] + preD[k] * (m - l + 1), preD[k<<1|1] += preD[k];
		sum[k<<1] += (2 * preB[k] + (m - l) * preD[k]) * (m - l + 1)/2;
		sum[k<<1|1] += (2 * preB[k] + (r - l + m + 1 - l) * preD[k]) * (r - m)/2;
		preB[k] = preD[k] = 0;
	}
	if(sufB[k]) {
		sufB[k<<1] += sufB[k] + (r - m) * sufD[k], sufD[k<<1] += sufD[k];
		sum[k<<1] += (2 * sufB[k] + (r - m + r - l) * sufD[k]) * (m - l + 1)/2;
		sufB[k<<1|1] += sufB[k], sufD[k<<1|1] += sufD[k];
		sum[k<<1|1] += (2 * sufB[k] + (r - m - 1) * sufD[k]) * (r - m)/2;
//		printf("[%d %d] suffix %lld %lld , = %lld %lld\n", l, r, sufB[k], sufD[k], sum[k<<1], sum[k<<1|1]);
		sufB[k] = sufD[k] = 0;
	}
}
void modifyA(int k, int l, int r, int x, int y) {
	if(l > r)	return;
	if(x <= l && r <= y)  {
		preB[k] += l - x + 1, preD[k]++;
		sum[k] += (LL)(2 * (l - x + 1) + r - l) * (r - l + 1)/2;
		return;
	}
	pushDown(k, l, r);
	int m = (l+r) /2;
	if(y <= m)
		modifyA(k<<1, l, m, x, y);
	else if(x > m)
		modifyA(k<<1|1, m+1, r, x, y);
	else {
		modifyA(k<<1, l, m, x, y);
		modifyA(k<<1|1, m+1, r, x, y);
	}
	pushUp(k);
}
void modifyB(int k, int l, int r, int x, int y) {
	if(l > r)	return;
	pushDown(k, l, r);
	if(x <= l && r <= y)  {
		sufB[k] += y - r + 1, sufD[k]++;
		sum[k] += (LL)(2 * (y - r + 1) + r - l) * (r - l + 1)/2;
//		printf("BB [%d %d] %d\n", l, r, base);
		return;
	}
	int m = (l+r) /2;
	if(y <= m)
		modifyB(k<<1, l, m, x, y);
	else if(x > m)
		modifyB(k<<1|1, m+1, r, x, y);
	else {
		modifyB(k<<1, l, m, x, y);
		modifyB(k<<1|1, m+1, r, x, y);
	}
	pushUp(k);
}
void modifyC(int k, int l, int r, int x, int y, int mm) {
	if(l > r)	return;
	if(x <= l && r <= y)  {
		setB[k] = 1, setD[k] = mm;
		preB[k] = preD[k] = sufB[k] = sufD[k] = 0;
		sum[k] = (LL)mm * (r - l + 1);
//		printf("CCCC [%d %d] %lld\n", l, r, sum[k]);
		return;
	}
	pushDown(k, l, r);
	int m = (l+r) /2;
	if(y <= m)
		modifyC(k<<1, l, m, x, y, mm);
	else if(x > m)
		modifyC(k<<1|1, m+1, r, x, y, mm);
	else {
		modifyC(k<<1, l, m, x, y, mm);
		modifyC(k<<1|1, m+1, r, x, y, mm);
	}
	pushUp(k);
}
long long query(int k, int l, int r, int x, int y) {
	if(l > r)	return 0;
	pushDown(k, l, r);
	if(x <= l && r <= y) {
//		printf("qq[%d %d] %lld\n", l, r, sum[k]);
		return sum[k];
	}
	int m = (l + r)/2;
	long long ret = 0;
	if(x <= m)
		ret += query(k<<1, l, m, x, y);
	if(y > m)
		ret += query(k<<1|1, m+1, r, x, y);
	return ret;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout); 
	int T, st, nd, x;
	char cmd[128];
	while(scanf("%d", &T) == 1) {
		memset(sum, 0, sizeof(sum));
		memset(preB, 0, sizeof(preB));
		memset(preD, 0, sizeof(preD));
		memset(sufB, 0, sizeof(sufB));
		memset(sufD, 0, sizeof(sufD));
		memset(setB, 0, sizeof(setB));
		memset(setD, 0, sizeof(setD));
		while(T--) {
			scanf("%s", cmd);
			if(cmd[0] == 'C')
				scanf("%d %d %d", &st, &nd, &x);
			else
				scanf("%d %d", &st, &nd);
			switch(cmd[0]) {
				case 'A':
					modifyA(1, 1, MAXN, st, nd);
					break;
				case 'B':
					modifyB(1, 1, MAXN, st, nd);
					break;
				case 'C':
					modifyC(1, 1, MAXN, st, nd, x);
					break;
				case 'S':
					long long ret = query(1, 1, MAXN, st, nd);
					printf("%lld\n", ret);
					break;
			}
		} 
	}
	return 0;
}
/*
1000
S 2 3
A 7 15
B 4 5
B 15 16
C 2 10 3
B 14 15
A 10 18
S 4 4
A 3 16
B 6 14
B 4 7
S 8 11
*/
