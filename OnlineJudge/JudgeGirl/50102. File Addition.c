#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#define MAXS (128)
#define BUFS (4096)
#define SWAP(x, y) do \
	{ uint8_t tmp[sizeof(x)]; \
		memcpy(tmp, &y, sizeof(x));\
		memcpy(&y, &x, sizeof(x)); \
		memcpy(&x, tmp, sizeof(x)); \
	} while (0)
#define min(x, y) ((x) < (y) ? (x) : (y))
void bin_add(FILE *fa, FILE *fb, FILE *fc) {
	fseek(fa, 0, SEEK_END);
	fseek(fb, 0, SEEK_END);
	int sa = ftell(fa), sb = ftell(fb);
	if (sa > sb) {
		SWAP(sa, sb);
		SWAP(fa, fb);
	}
	int sc = sb;
	fseek(fc, sc, SEEK_SET);
	
	uint8_t carry = 0;
	static uint8_t ba[BUFS], bb[BUFS];
	while (sa && sb) {
		int n = min(min(sa, sb), BUFS);
		fseek(fa, -n, SEEK_CUR);
		fread(ba, sizeof(uint8_t), n, fa);
		fseek(fa, -n, SEEK_CUR);
		fseek(fb, -n, SEEK_CUR);
		fread(bb, sizeof(uint8_t), n, fb);
		fseek(fb, -n, SEEK_CUR);
		for (int i = n-1; i >= 0; i--) {
			uint8_t t = ba[i];
			ba[i] = t + carry;
			carry = ba[i] < t;
			t = bb[i];
			ba[i] = ba[i] + t;
			carry |= ba[i] < t;
		}
		fseek(fc, -n, SEEK_CUR);
		fwrite(ba, sizeof(uint8_t), n, fc);
		fseek(fc, -n, SEEK_CUR);
		sa -= n, sb -= n;
	}
	while (sb) {
		int n = min(sb, BUFS);
		fseek(fb, -n, SEEK_CUR);
		fread(bb, sizeof(uint8_t), n, fb);
		fseek(fb, -n, SEEK_CUR);
		for (int i = n-1; i >= 0; i--) {
			uint8_t t = bb[i];
			ba[i] = t + carry;
			carry = ba[i] < t;
		}
		fseek(fc, -n, SEEK_CUR);
		fwrite(ba, sizeof(uint8_t), n, fc);
		fseek(fc, -n, SEEK_CUR);
		sb -= n;
	}
}

int main() {
	char sa[MAXS], sb[MAXS], sc[MAXS];
	scanf("%s %s %s", sa, sb, sc);
	FILE *fa = fopen(sa, "rb"), *fb = fopen(sb, "rb");
	FILE *fc = fopen(sc, "wb");
	assert(fa && fb && fc);
	bin_add(fa, fb, fc);
	fclose(fa), fclose(fb), fclose(fc);
	return 0;
}
