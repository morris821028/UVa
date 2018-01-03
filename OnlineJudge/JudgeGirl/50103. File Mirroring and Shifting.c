#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#define MAXS 128
#define BUFS 8192
static inline uint8_t reverse(uint8_t a) {
    a = ((a & 0x55)<<1) | ((a & 0xAA)>>1);
    a = ((a & 0x33)<<2) | ((a & 0xCC)>>2);
    a = ((a & 0x0F)<<4) | ((a & 0xF0)>>4);
    return a;
}
void bin_shiftm(FILE *fin, FILE *fout, int shift) {
	int n, size;
	static uint8_t buf[BUFS];
	
	fseek(fin, 0, SEEK_END);
	size = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	shift = (size-shift%size)%size;
	int pos = 0;
	while ((n = fread(buf, sizeof(uint8_t), BUFS,  fin))) {
		for (int i = 0; i < n; i++)
			buf[i] = reverse(buf[i]);
		for (int i = 0, j = n-1; i < j; i++, j--) {
			uint8_t t = buf[i];
			buf[i] = buf[j];
			buf[j] = t;
		}
		int wpos = (size - (pos+n) + shift)%size;
		fseek(fout, wpos, SEEK_SET);
		if (wpos + n < size) {
			fwrite(buf, sizeof(uint8_t), n, fout);
		} else {
			int m = wpos+n - size;
			fwrite(buf, sizeof(uint8_t), n-m, fout);
			fseek(fout, 0, SEEK_SET);
			fwrite(buf+n-m, sizeof(uint8_t), m, fout);
		}
		pos += n;
	}
}
int main() {
	char sa[MAXS], sb[MAXS];
	int x;
    scanf("%s %s %d", sa, sb, &x);
    FILE *fin = fopen(sa, "rb"), *fout = fopen(sb, "wb");
    assert(fin && fout);
    bin_shiftm(fin, fout, x);
    fclose(fin), fclose(fout);
	return 0;
}
