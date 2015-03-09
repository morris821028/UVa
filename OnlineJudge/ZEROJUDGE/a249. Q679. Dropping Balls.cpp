#include<stdio.h>
int reverse(int D, int I) {
	static int i, tmp;
	D-=2, I--;
	for(i = 0, tmp = 0; i <= D; i++) {
		tmp |= (((1<<(D-i))&I) != 0) << i;
	}
	return tmp;
};
int main() {
	int t, D, I, pos;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &D, &I);
		pos = 1 << (D-1);
		printf("%d\n", pos + reverse(D, I));
	}
	return 0;
}
