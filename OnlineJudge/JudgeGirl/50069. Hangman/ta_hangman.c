#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hangman.h"

struct Hangman{
	int g, G;
	char answer[MAXL];
	int status[26]; // -1: not in answer, 0: in answer, not guessed, 1: in answer, guessed
};

Hangman* newGame(char *answer, int G){
	Hangman *hangman = (Hangman*) malloc(sizeof(Hangman));
	hangman->g = 0, hangman->G = G;
	strcpy(hangman->answer, answer);
	for(int i = 0; i < 26; i++)
		hangman->status[i] = -1;
	int L = strlen(answer);
	for(int i = 0; i < L; i++)
		hangman->status[answer[i] - 'a'] = 0;
	return hangman;
}

int guess(Hangman* hangman, char ch){
	int s = hangman->status[ch - 'a'];
	if (s == -1){
		hangman->g++;
		if (hangman->g == hangman->G) return -1;
		return 0;
	}
	hangman->status[ch - 'a'] = 1;
	return 1;
}

void printStatus(Hangman* hangman){
	int L = strlen(hangman->answer);
	for(int i = 0; i < L; i++){
		if (hangman->status[hangman->answer[i] - 'a'] == 1)
			printf("%c", hangman->answer[i]);
		else printf("*");
	}
	printf("\n");
}

int solved(Hangman* hangman){
	for(int i = 0; i < 26; i++)
		if (hangman->status[i] == 0) return 0;
	return 1;
}

