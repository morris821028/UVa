#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef unsigned long UINT32;
typedef unsigned long long UINT64;
UINT32 F(UINT32 x, UINT32 y, UINT32 z) {
	return (x & y) | (~x & z);
}
UINT32 G(UINT32 x, UINT32 y, UINT32 z) {
	return (x & z) | (y & ~z);
}
UINT32 H(UINT32 x, UINT32 y, UINT32 z) {
	return x ^ y ^ z;
}
UINT32 I(UINT32 x, UINT32 y, UINT32 z) {
	return y ^ (x | ~z);
}
UINT32 rotate_left(UINT32 x, UINT32 n) {
	return  (x << n) | (x >> (32-n));
}
void MD5(char in[]) {
	UINT32 S[4][4] = {{7, 12, 17, 22}, {5, 9, 14, 20}, {4, 11, 16, 23}, {6, 10, 15, 21}};
	UINT32 X[16], T[65], chain[4] ={0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
	UINT32 Xinit[4][2] = {{0, 1}, {1, 5}, {5, 3}, {0, 7}};
	int i, j, roundIdx, xIdx, sIdx;
	UINT32 ( *Function[4])(UINT32, UINT32, UINT32) = {F, G, H, I};
	for(i = 1; i <= 64; i++)	T[i] = (UINT32)floor((1ULL << 32)*fabs(sin(i)));
	UINT32 length = strlen(in)+1, bit_length = 8*length, tlength = (length-1)*8;
	UINT32 Copy[length+513], supply, state[4];
	for(i = 0; i < length; i++)	Copy[i] = in[i] < 0 ? (128-abs(in[i]))+(1<<7) : in[i];
	Copy[length-1] = 1 << 7;
	supply = bit_length % 512;
	supply = (supply > 448) ? (512-supply+448) : (448-supply);
	for(i = supply/8; i >= 0; i--, length++)	Copy[length] = 0;
	for(i = length-1; tlength; i++)
		Copy[i] = tlength % 256, tlength /= 256;
	bit_length = (length-1)*8+64, length = bit_length/8;
	for(i = 0; i < length; i += 64) {
		state[0] = chain[0], state[1] = chain[1];
		state[2] = chain[2], state[3] = chain[3];
		for(j = 0; j < 16; j++)
			X[j] = (Copy[i+j*4+3]<<24) | (Copy[i+j*4+2]<<16) | (Copy[i+j*4+1]<<8) | Copy[i+j*4];
		for(roundIdx = 0; roundIdx < 4; roundIdx++) {
			xIdx = Xinit[roundIdx][0], sIdx = 0;
			for(j = 0; j < 16; j++) {
				state[sIdx] = state[(sIdx+1)%4] + rotate_left(
					state[sIdx] + ( *Function[roundIdx])(state[(sIdx+1)%4], state[(sIdx+2)%4], state[(sIdx+3)%4])
					+ X[xIdx] + T[roundIdx*16+j+1], S[roundIdx][j%4]
				);
				sIdx = (sIdx + 3) % 4;
				xIdx = (xIdx + Xinit[roundIdx][1]) & 0xF;
			}
		}
		chain[0] += state[0], chain[1] += state[1];
		chain[2] += state[2], chain[3] += state[3];
	}
	char r[33];
	for(i = 0; i < 4; i++)
		for(j = 0; j < 8; j += 2)
			sprintf(r+i*8+j, "%02X", chain[i] & 0xff), chain[i] >>= 8;
	r[32] = '\0';
	puts(r);
}
main() {
	char S[20000];
	while(gets(S))			
		MD5(S);
	return 0;
}
