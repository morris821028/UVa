#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAXLINEC 2048
char buf[MAXLINEC];

int fsize(FILE *fp) {
	int prev = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, prev, SEEK_SET);
	return size;
}
int countWord(char buf[]) {
	int ret = 0, n = strlen(buf);
	for (int i = 0; i < n; i++) {
		if (isalpha(buf[i])) {
			while (isalpha(buf[i]))
				i++;
			ret++;
		}
	}
	return ret;
}
int main() {
	char fName[128];
	scanf("%s", fName);
	FILE *fin = fopen(fName, "r");
	
	assert(fin != NULL);
	
	int ret[3] = {0, 0, fsize(fin)};
	while (fgets(buf, MAXLINEC, fin)) {
		ret[0]++;
		ret[1] += countWord(buf);
	}
	printf("%d %d %d\n", ret[0], ret[1], ret[2]);
	return 0;
}
