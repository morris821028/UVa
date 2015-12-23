#include "fs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int isValid(Account *f) {
	if (f->balance < 0)	
		return 0;
	if (f->gender != 0 && f->gender != 1)
		return 0;
	for (int i = 0; f->name[i]; i++) {
		if (!isalpha(f->name[i]) && f->name[i] != ' ')
			return 0;
	}
	return 1;
}
int cmp(const void *x, const void *y) {
	return strcmp(((Account *) x)->name, ((Account *) y)->name);
}
Account fs[65536];
int main() {
	char ifName[128], ofName[128];
	scanf("%s %s", ifName, ofName);
	
	int n = 0;
	Account tmp;
	FILE *fin = fopen(ifName, "rb");
	FILE *fout = fopen(ofName, "wb");
	
	assert(fin != NULL);
	assert(fout != NULL);
	while (fread(&tmp, sizeof(Account), 1, fin)) {
		if (isValid(&tmp))
			fs[n++] = tmp;
	}
	
	qsort(fs, n, sizeof(Account), cmp);
	fwrite(fs, sizeof(Account), n, fout);
	fclose(fout);
	fclose(fin);
	return 0;
}
