#include "tct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int printSep(int n, int gap[], int newline, Directory *path[]) {
	putchar(' ');
	for (int i = 1; i < n; i++) {
		int m = gap[i] - gap[i-1];
		while (m--)	putchar(' ');
		if (path[i+1] != NULL && path[i+1]->silbingDir != NULL)
			putchar('|');
		else
			putchar(' ');
	}
	if (newline)
		puts("");
}
static int rprint(int dep, int padding, Directory *dir, int gap[], Directory *path[]) {
	Directory *u = dir->childDir;
	gap[dep] = padding, path[dep] = dir;
	if (dir->childDir != NULL) {
		printSep(dep, gap, 0, path);
		puts("  |");
	}
	while (u != NULL) {
		printSep(dep, gap, 0, path);
		printf("  +- %s\n", u->name);
		rprint(dep+1, padding+2, u, gap, path);
		u = u->silbingDir;
		if (u != NULL) {
			printSep(dep, gap, 0, path);
			puts("  |");
		}
	}
}
void tree(Directory *fs) {
	printf("+- %s\n", fs->name);
	int lines = 0, gap[256] = {2};
	Directory *path[256] = {NULL};
	rprint(1, 4, fs, gap, path);
}
Directory* cd(Directory *fs, char path[]) {
	Directory *ret = fs;
	char *p = strtok(path, "/");
	while (p != NULL) {
		Directory *u = ret->childDir;
		while (u != NULL) {
			if (!strcmp(u->name, p))
				break;
			u = u->silbingDir;
		}
		if (u == NULL)	return NULL;
		ret = u;
		p = strtok(NULL, "/");
	}
	return ret;
}
