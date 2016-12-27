#include "hangman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Hangman {
	char s[MAXL];
	char has[128];
	int n, m;
};
typedef struct Hangman Hangman; 
 
Hangman* newGame(char *s, int n) {
	Hangman *ret = (Hangman*) malloc(sizeof(Hangman));
	ret->n = n;
	ret->m = 0;
	memset(ret->has, 0, sizeof(ret->has[0])*128);
	strcpy(ret->s, s);
	for (int i = 0; s[i]; i++)
		ret->has[s[i]] = 1;
	for (int i = 0; i < 128; i++)
		ret->m += ret->has[i] == 1;
	return ret;
}
int guess(Hangman *h, char c) {
	if (h->has[c] > 0) {
		h->m -= h->has[c] == 1;
		h->has[c] = 2;
		return 1;
	}
	if (--(h->n) <= 0)
		return -1;
	return 0;
}
void printStatus(Hangman *h) {
	for (int i = 0; h->s[i]; i++)
		putchar(h->has[h->s[i]] == 2 ? h->s[i] : '*');
	puts("");
}
int solved(Hangman* h) {
	return h->m == 0;	
}

