#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *x, const void *y) {
	return strcmp(*(char **)x, *(char **)y);
}
int main() {
	char lines[128][128];
	char *ptr[128];
	int n = 0;
	while (fgets(lines[n], 128, stdin))
		ptr[n] = lines[n], n++;
	qsort(ptr, n, sizeof(char*), cmp);
	for (int i = 0; i < n; i++)
		printf("%s", ptr[i]);
	return 0;
}
