#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

int main() {
	char fName[128];
	scanf("%s", fName);
	FILE *fin = fopen(fName, "r");
	
	assert(fin != NULL);
	
	char c;
	int ret[3] = {0, 0, 0};
	int hasLetter = 0, lineChar = 0;
	while ((c = fgetc(fin)) != EOF) {
		ret[2]++;
		if (isalpha(c)) {
			hasLetter = 1, lineChar++;
		} else if (c == '\n') {
			if (hasLetter)
				ret[1]++, hasLetter = 0;
			ret[0]++, lineChar = 0;
		} else {
			if (hasLetter)
				ret[1]++, hasLetter = 0;
			lineChar++;
		}
	}
	if (lineChar)	
		ret[0]++, lineChar = 0;
	if (hasLetter)
		ret[1]++, hasLetter = 0;
	printf("%d %d %d\n", ret[0], ret[1], ret[2]);
	return 0;
}
