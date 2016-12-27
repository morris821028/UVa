all: ta_main stu_main

ta_main: ta_main.c hangman.c
	gcc -std=c99 -O2 ta_main.c hangman.c -o ta_main

stu_main: main.c ta_hangman.c
	gcc -std=c99 -O2 main.c ta_hangman.c -o stu_main
