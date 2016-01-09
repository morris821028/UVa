#include "tct.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

Directory* mkDir(char name[]) {
	Directory *d = (Directory *) malloc(sizeof(Directory));
	strcpy(d->name, name);
	d->silbingDir = d->childDir = NULL;
	return d;
}
Directory* newDir(char name[], int n, ...) {
	va_list args;
	va_start(args, n);
	Directory *u = mkDir(name), *p = NULL;
	for (int i = 0; i < n; i++) {
		Directory *para = va_arg(args, Directory*);
		if (i == 0)	
			u->childDir = para;
		if (p != NULL)
			p->silbingDir = para;
		p = para;
	}
	va_end(args);
	return u;
}
int main() {
	Directory *fs =
		newDir("root", 3,
			newDir("home", 2,
				newDir("morris", 1,
					newDir("workspace", 0)),
				newDir("stephanie", 0))
			, newDir("etc", 0)
			, newDir("bin", 2
				, newDir("arch", 0)
				, newDir("cat", 0))
		);
	tree(fs);
	
	char path[128] = "home/morris";
	tree(cd(fs, path));
	tree(fs);
	strcpy(path, "home/morris/workspace");
	tree(cd(fs, path));
	return 0;
}
