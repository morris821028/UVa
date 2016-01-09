#ifndef _TCT_H
#define _TCT_H

typedef struct Directory {
	char name[256];
	struct Directory *childDir;
	struct Directory *silbingDir;
} Directory;

void tree(Directory *fs);
Directory* cd(Directory *fs, char path[]);

#endif
