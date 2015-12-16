#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#define MAXVAL 65536
char fileName[128];
unsigned char *buf;
int32_t fetch32bits(unsigned char **p) {
	int32_t *tp = (int16_t *) *p;
	(*p) += 4;
	return *tp;
}
int16_t fetch16bits(unsigned char **p) {
	int16_t *tp = (int16_t *) *p;
	(*p) += 2;
	return *tp;
}
int fsize(FILE *fp) {
    int prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fseek(fp, prev, SEEK_SET);
    return size;
}
int main() {
	scanf("%s", fileName);
	FILE *fin = fopen(fileName, "rb");
	int finsize = fsize(fin);
	buf = malloc(sizeof(unsigned char)*finsize);
	int size_n = fread(buf, 1, finsize, fin);
	unsigned char *ptr = buf;
	int32_t n = fetch32bits(&ptr);
	int cnt[MAXVAL] = {};
	for (int i = 0; i < n; i++) {
		int16_t x = fetch16bits(&ptr);
		cnt[x + 32768]++;
	}
	
	int ret, mx = 0;
	for (int i = MAXVAL-1; i >= 0; i--) {
		if (cnt[i] > mx)
			mx = cnt[i], ret = i;
	}
	printf("%d\n%d\n", ret - 32768, mx);
	free(buf);
	return 0;
}
