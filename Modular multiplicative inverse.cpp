#include<stdio.h>
int Calu_Mod_Inverse(int x, int y) {
	int t, mod = y;
	int ra = 1, rn = 0, la = 0, ln = 1, step = 1;
	while(x%y) {
		if(step) {
			ra -= x/y * la;
			rn -= x/y * ln;
		} else {
			la -= x/y * ra;
			ln -= x/y * rn;
		}
		t = x, x = y, y = t%y;
		step = 1 - step;
	}
	if(y == 1) {
		if(step)
			return (la%mod + mod)%mod;
		else
			return (ra%mod + mod)%mod;
	}
	else
		return 0;
}
int main() {
	int a, n, tmp;
	while(scanf("%d %d", &a, &n) == 2) {
		tmp = Calu_Mod_Inverse(a, n);
		if(tmp)		printf("%d\n", tmp);
		else		puts("No Inverse");
	}
	return 0;
}
