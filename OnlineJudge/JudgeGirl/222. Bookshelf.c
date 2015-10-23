#include <stdio.h>
#define UINT64 unsigned long long
const UINT64 pre[8] = {
0, 0xffffffffffffff00, 0xffffffffffff0000, 0xffffffffff000000, 0xffffffff00000000,
0xffffff0000000000, 0xffff000000000000, 0xff00000000000000
};
const UINT64 suf[8] = {
0, 0x00000000000000ff, 0x000000000000ffff, 0x0000000000ffffff, 0x00000000ffffffff,
0x000000ffffffffff, 0x0000ffffffffffff, 0x00ffffffffffffff
};
int bt[256] = { [1] = 1, [2] = 2, [4] = 3, [8] = 4, [16] = 5, [32] = 6, [64] = 7, [128] = 8 };
int main() {
	UINT64 b = 0;
	int x;
	while (scanf("%d", &x) == 1) {
		int pos;
		pos = ((b&0x00000000000000ff) == x) |
				(((b&0x000000000000ff00)>>8) == x)<<1 |
				(((b&0x0000000000ff0000)>>16) == x)<<2 |
				(((b&0x00000000ff000000)>>24) == x)<<3 |
				(((b&0x000000ff00000000)>>32) == x)<<4 |
				(((b&0x0000ff0000000000)>>40) == x)<<5 |
				(((b&0x00ff000000000000)>>48) == x)<<6;
		if (pos == 0) {
			b = (b<<8) | x;
			continue;
		}
		pos = bt[pos];
		b = b&pre[pos] | ((b&suf[pos])<<8)&suf[pos] | x;
	}	
	for (int i = 7; i >= 0; i--)
		printf("%d%c", (b>>(i<<3))&255, " \n"[i==0]);
	return 0;
}

