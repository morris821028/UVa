#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXBUF (1<<21)
char buffer[MAXBUF];
int main(int argc, char* argv[]) {
	assert(argc == 1+2);
	FILE *file = fopen(argv[1], "rb");
	assert(file != NULL);
	int blocksize = atoi(argv[2]), n;
	assert(blocksize < MAXBUF);
	int counter = 0;
	while ((n = fread(buffer, sizeof(char), blocksize, file))) {
		char pfilename[256];
		sprintf(pfilename, "%s-%03d", argv[1], counter);
		FILE *pfile = fopen(pfilename, "wb");
		fwrite(buffer, sizeof(char), n, pfile);
		fclose(pfile);
		counter++;
	}
	fclose(file);
	return 0;
}

