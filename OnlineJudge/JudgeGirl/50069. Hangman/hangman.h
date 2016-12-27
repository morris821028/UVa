#ifndef HANGMAN_H
#define HANGMAN_H

#define MAXL 105
#define MAXGL 205
struct Hangman;
typedef struct Hangman Hangman;
 
Hangman* newGame(char *answer, int G);
int guess(Hangman* hangman, char ch);
void printStatus(Hangman* hangman);
int solved(Hangman* hangman);

#endif
