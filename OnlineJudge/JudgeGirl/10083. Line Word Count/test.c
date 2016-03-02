#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int fsize(FILE *fp) {
    int prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    fseek(fp, prev, SEEK_SET);
    return size;
}
void computeline(char line[], int n) {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (isalpha(line[i])) {
			while (i < n && isalpha(line[i]))
				i++;
			ret++;
		}
	}
	printf("%d\n", ret);
}
#define MAXBUFSIZE (2<<20)
void wordcount(char filename[]) {
	FILE *file = fopen(filename, "r");
	static char line[MAXBUFSIZE];
	while (fgets(line, MAXBUFSIZE, file)) {
		computeline(line, strlen(line));
	}
}
int main() {
//	for (int i = 0; i < 42; i++)
//		printf("in.txt-%03d\n", i);
	char filename[1024];
	scanf("%s", filename);
	wordcount(filename);
	return 0;
}
