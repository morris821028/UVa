#include <stdio.h>
#include <stdlib.h>

#define MAXN 1048576*8
int A[MAXN];

int cmp(const void *x, const void *y) {
	return *(int *) x - *(int *) y;
}

int main() {
	char fName[128], ofName[128];
	scanf("%s %s", fName, ofName);
	FILE *fin = fopen(fName, "rb");
	FILE *fout = fopen(ofName, "wb");
	
	int n = fread(A, sizeof(int), MAXN, fin);

	qsort(A, n, sizeof(int), cmp);
	
	fwrite(A, sizeof(int), n, fout);
	fclose(fout);
	return 0;
}

