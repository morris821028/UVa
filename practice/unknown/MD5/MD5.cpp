#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
unsigned F(unsigned x, unsigned y, unsigned z) {
	return (x & y) | (~x & z);
}
unsigned G(unsigned x, unsigned y, unsigned z) {
	return (x & z) | (y & ~z);
}
unsigned H(unsigned x, unsigned y, unsigned z) {
	return x ^ y ^ z;
}
unsigned I(unsigned x, unsigned y, unsigned z) {
	return y ^ (x | ~z);
}
unsigned rotate(unsigned x, unsigned n) {
	return  (x << n) | (x >> (32-n));
}
void FF( unsigned *a,  unsigned *b,  unsigned *c,  unsigned *d,  unsigned *xk,  unsigned *s,  unsigned *ti) {
	*a = (*b) + rotate(*a+F(*b, *c, *d)+(*xk)+(*ti), (*s));
}
void GG( unsigned *a,  unsigned *b,  unsigned *c,  unsigned *d,  unsigned *xk,  unsigned *s,  unsigned *ti) {
	*a = (*b) + rotate(*a+G(*b, *c, *d)+(*xk)+(*ti), (*s));
}
void HH( unsigned *a,  unsigned *b,  unsigned *c,  unsigned *d,  unsigned *xk,  unsigned *s,  unsigned *ti) {
	*a = (*b) + rotate(*a+H(*b, *c, *d)+(*xk)+(*ti), (*s));
}
void II( unsigned *a,  unsigned *b,  unsigned *c,  unsigned *d,  unsigned *xk,  unsigned *s,  unsigned *ti) {
	*a = (*b) + rotate(*a+I(*b, *c, *d)+(*xk)+(*ti), (*s));
}
void transfrom(unsigned n, unsigned set, unsigned M[]) {
	if(n == 0)	return ;
	transfrom(n/2, set-1, M);
	M[set] = n&1;
}
main() {
	int C = 0, T, Cc = 0;
	char S[20000], check[100];			
	unsigned s[65] = {0, 7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21};
	unsigned X[16];
	unsigned t[65] = {0, 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af
		, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa
		, 0xd62f105d,  0x2441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8
		, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70
		, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085,  0x4881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97
		, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1
		, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
	while(scanf("%d", &T) == 1) {
		getchar();
		printf("Case %d#:\n", ++C);
		while(T--) {
			gets(S), gets(check);
			int L = strlen(S)+1, bit_length, supply, tL = (L-1)*8;
			unsigned Copy[20000] = {};
			unsigned a, b, c, d;
			int i, j, k;
			bit_length = L*8, supply = bit_length%512;
			if(supply > 448)	supply = 512-supply+448;
			else	supply = 448-supply;
			for(i = 0; i < L; i++)	{
				if(S[i] < 0)
					Copy[i] = (128-abs(S[i])) + (1 << 7);
				else
					Copy[i] = S[i];
			}
			Copy[L-1] = 1<<7;
			for(i = L, j = supply/8; j >= 0; i++, j--)
				Copy[i] = 0;
			L = i;
			for(i = L-1; tL; i++)
				Copy[i] = tL % 256,	tL /= 256;
			bit_length = (L-1)*8+64, L = bit_length/8;
			unsigned A = 0x67452301, B = 0xefcdab89, C = 0x98badcfe, D = 0x10325476;
			for(i = 0; i < L; i += 64) {
				a = A, b = B, c = C, d = D;
				for(j = 0; j < 16; j++) {
					X[j] = (Copy[i+j*4+3]<<24) | (Copy[i+j*4+2]<<16) | (Copy[i+j*4+1]<<8) | Copy[i+j*4];
				}
				FF(&a, &b, &c, &d, &X[ 0], &s[1], &t[1]);
				FF(&d, &a, &b, &c, &X[ 1], &s[2], &t[2]);
				FF(&c, &d, &a, &b, &X[ 2], &s[3], &t[3]);
				FF(&b, &c, &d, &a, &X[ 3], &s[4], &t[4]);
				FF(&a, &b, &c, &d, &X[ 4], &s[1], &t[5]);
				FF(&d, &a, &b, &c, &X[ 5], &s[2], &t[6]);
				FF(&c, &d, &a, &b, &X[ 6], &s[3], &t[7]);
				FF(&b, &c, &d, &a, &X[ 7], &s[4], &t[8]);
				FF(&a, &b, &c, &d, &X[ 8], &s[1], &t[9]);
				FF(&d, &a, &b, &c, &X[ 9], &s[2], &t[10]);
				FF(&c, &d, &a, &b, &X[10], &s[3], &t[11]);
				FF(&b, &c, &d, &a, &X[11], &s[4], &t[12]);
				FF(&a, &b, &c, &d, &X[12], &s[1], &t[13]);
				FF(&d, &a, &b, &c, &X[13], &s[2], &t[14]);
				FF(&c, &d, &a, &b, &X[14], &s[3], &t[15]);
				FF(&b, &c, &d, &a, &X[15], &s[4], &t[16]);
				
				GG(&a, &b, &c, &d, &X[ 1], &s[5], &t[17]);
				GG(&d, &a, &b, &c, &X[ 6], &s[6], &t[18]);
				GG(&c, &d, &a, &b, &X[11], &s[7], &t[19]);
				GG(&b, &c, &d, &a, &X[ 0], &s[8], &t[20]);
				GG(&a, &b, &c, &d, &X[ 5], &s[5], &t[21]);
				GG(&d, &a, &b, &c, &X[10], &s[6], &t[22]);
				GG(&c, &d, &a, &b, &X[15], &s[7], &t[23]);
				GG(&b, &c, &d, &a, &X[ 4], &s[8], &t[24]);
				GG(&a, &b, &c, &d, &X[ 9], &s[5], &t[25]);
				GG(&d, &a, &b, &c, &X[14], &s[6], &t[26]);
				GG(&c, &d, &a, &b, &X[ 3], &s[7], &t[27]);
				GG(&b, &c, &d, &a, &X[ 8], &s[8], &t[28]);
				GG(&a, &b, &c, &d, &X[13], &s[5], &t[29]);
				GG(&d, &a, &b, &c, &X[ 2], &s[6], &t[30]);
				GG(&c, &d, &a, &b, &X[ 7], &s[7], &t[31]);
				GG(&b, &c, &d, &a, &X[12], &s[8], &t[32]);

				HH(&a, &b, &c, &d, &X[ 5], &s[9], &t[33]);
				HH(&d, &a, &b, &c, &X[ 8], &s[10], &t[34]);
				HH(&c, &d, &a, &b, &X[11], &s[11], &t[35]);
				HH(&b, &c, &d, &a, &X[14], &s[12], &t[36]);
				HH(&a, &b, &c, &d, &X[ 1], &s[9], &t[37]);
				HH(&d, &a, &b, &c, &X[ 4], &s[10], &t[38]);
				HH(&c, &d, &a, &b, &X[ 7], &s[11], &t[39]);
				HH(&b, &c, &d, &a, &X[10], &s[12], &t[40]);
				HH(&a, &b, &c, &d, &X[13], &s[9], &t[41]);
				HH(&d, &a, &b, &c, &X[ 0], &s[10], &t[42]);
				HH(&c, &d, &a, &b, &X[ 3], &s[11], &t[43]);
				HH(&b, &c, &d, &a, &X[ 6], &s[12], &t[44]);
				HH(&a, &b, &c, &d, &X[ 9], &s[9], &t[45]);
				HH(&d, &a, &b, &c, &X[12], &s[10], &t[46]);
				HH(&c, &d, &a, &b, &X[15], &s[11], &t[47]);
				HH(&b, &c, &d, &a, &X[ 2], &s[12], &t[48]);
				
				II(&a, &b, &c, &d, &X[ 0], &s[13], &t[49]);
				II(&d, &a, &b, &c, &X[ 7], &s[14], &t[50]);
				II(&c, &d, &a, &b, &X[14], &s[15], &t[51]);
				II(&b, &c, &d, &a, &X[ 5], &s[16], &t[52]);
				II(&a, &b, &c, &d, &X[12], &s[13], &t[53]);
				II(&d, &a, &b, &c, &X[ 3], &s[14], &t[54]);
				II(&c, &d, &a, &b, &X[10], &s[15], &t[55]);
				II(&b, &c, &d, &a, &X[ 1], &s[16], &t[56]);
				II(&a, &b, &c, &d, &X[ 8], &s[13], &t[57]);
				II(&d, &a, &b, &c, &X[15], &s[14], &t[58]);
				II(&c, &d, &a, &b, &X[ 6], &s[15], &t[59]);
				II(&b, &c, &d, &a, &X[13], &s[16], &t[60]);
				II(&a, &b, &c, &d, &X[ 4], &s[13], &t[61]);
				II(&d, &a, &b, &c, &X[11], &s[14], &t[62]);
				II(&c, &d, &a, &b, &X[ 2], &s[15], &t[63]);
				II(&b, &c, &d, &a, &X[ 9], &s[16], &t[64]);
				A += a, B += b, C += c, D += d;
			} 
			char r[33];
			sprintf(r, "%02x", A&0xff), A >>= 8;
			sprintf(r+2, "%02x", A&0xff), A >>= 8;
			sprintf(r+4, "%02x", A&0xff), A >>= 8;
			sprintf(r+6, "%02x", A&0xff), A >>= 8;
			sprintf(r+8, "%02x", B&0xff), B >>= 8;
			sprintf(r+10, "%02x", B&0xff), B >>= 8;
			sprintf(r+12, "%02x", B&0xff), B >>= 8;
			sprintf(r+14, "%02x", B&0xff), B >>= 8;
			sprintf(r+16, "%02x", C&0xff), C >>= 8;
			sprintf(r+18, "%02x", C&0xff), C >>= 8;
			sprintf(r+20, "%02x", C&0xff), C >>= 8;
			sprintf(r+22, "%02x", C&0xff), C >>= 8;
			sprintf(r+24, "%02x", D&0xff), D >>= 8;
			sprintf(r+26, "%02x", D&0xff), D >>= 8;
			sprintf(r+28, "%02x", D&0xff), D >>= 8;
			sprintf(r+30, "%02x", D&0xff), D >>= 8;
			r[32] = '\0';
			if(strcmp(r ,check) == 0)
				printf("Passed %s = %s\n", S, check);
			else
				printf("Failed %s = %s <> %s\n", S, r, check);
		}
	}
	return 0;
}
