#include "count.h"
#include <ctype.h>
void count(char *string, int *nchar, int *nword, int *ntokens, int *nline) {
	*nchar = *nword = *ntokens = *nline = 0;
	for (int i = 0; string[i]; i++)	(*nchar)++;
	for (int i = 0; string[i]; i++) {
		if (isalpha(string[i])) {
			while (string[i] && isalpha(string[i]))
				i++;
			(*nword)++;
		}
	}
	for (int i = 0; string[i]; i++) {
		if (!isspace(string[i])) {
			while (string[i] && !isspace(string[i]))
				i++;
			(*ntokens)++;
		}
	}
	for (int i = 0; string[i]; i++)
		if (string[i] == '\n')
			(*nline)++;
}
