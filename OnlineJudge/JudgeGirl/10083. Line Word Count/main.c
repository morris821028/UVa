#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

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
FILE* readfile(char filename[], int fidx) {
	static char subname[256];
	sprintf(subname, "%s-%03d", filename, fidx);
	return fopen(subname, "rb");
}
void parsefile(char filename[], int fidx) {
	static char buff[MAXBUFSIZE], line[MAXBUFSIZE];
	FILE *cfp = readfile(filename, fidx);
	char *bptr = buff, *bend = buff, *lptr = line;
	
	if (fidx != 0) {	// find next line begin
		while (1) {
			// add buffer
			if (bptr == bend) {
				if ((bend = buff + fread(buff, sizeof(char), MAXBUFSIZE, cfp)) == buff)
					return ;
				bptr = buff;
			}
			// ignore incomplete line
			while (bptr != bend && (*bptr) != '\n')
				bptr++;
			// new line start
			if (bptr != bend && (*bptr) == '\n') {
				bptr++; break;
			}
		}
	} else {
		if ((bend = buff + fread(buff, sizeof(char), MAXBUFSIZE, cfp)) == buff)
			return ;
		bptr = buff;
	}
	
	if (bptr == bend && feof(cfp))
		return ;
	
	int ret = 0, cross = 0, lastchar = 0;
	for (; ; ) {
		// add buffer
		if (bptr == bend) {
			if ((bend = buff + fread(buff, sizeof(char), MAXBUFSIZE, cfp)) == buff) {
				cross = 1;
				// load next file
				fidx++, cfp = readfile(filename, fidx);
				if (cfp == NULL)
					return ;
				if ((bend = buff + fread(buff, sizeof(char), MAXBUFSIZE, cfp)) == buff)
					return ;
			}
			bptr = buff;
		}
		// add line
		lastchar = 0;
		while (bptr != bend && (*bptr) != '\n')	
			*lptr = *bptr, lptr++, bptr++;
		if (bptr != bend && (*bptr) == '\n') {
			computeline(line, lptr - line);
			bptr++, lptr = line;
			lastchar = '\n';
			if (cross && (bptr != bend || !feof(cfp)))
				return ;
		}
	}
}
void wordcount(char filename[], int n) {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		FILE *cfile = readfile(filename, i);
		assert(cfile != NULL);
		parsefile(filename, i);
	}
}
int main() {
	char filename[1024];
	int n, ret;
	scanf("%s %d", filename, &n);
	wordcount(filename, n);
	return 0;
}
