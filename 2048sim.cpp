#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <conio.h> 
#include <time.h>
#include <windows.h>
#include <math.h> 
HANDLE hConsole;

const int H = 5;
int board[H][H];
void repeatPrint(char str[], int n) {
	while(n--)	printf(str);
	puts("");
}
void printBoard() {
	repeatPrint("======", H);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for(int i = 0; i < H; i++) {
		for(int j = 0; j < H; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if(board[i][j] > 0)
				SetConsoleTextAttribute(hConsole, ((int)(log2(board[i][j])))%6 + 10);
			printf("|%4s|", "");			
		}
		puts("");
		for(int j = 0; j < H; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if(board[i][j] > 0) {
				SetConsoleTextAttribute(hConsole, ((int)(log2(board[i][j])))%6 + 10);
				printf("|%4d|", board[i][j]);
			} else
				printf("|%4s|", "");
		}
		puts("");		
		for(int j = 0; j < H; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if(board[i][j] > 0)
				SetConsoleTextAttribute(hConsole, ((int)(log2(board[i][j])))%6 + 10);
			printf("|%4s|", "");			
		}
		puts("");
		SetConsoleTextAttribute(hConsole, 15);
		repeatPrint("======", H);
	}
}
void generateBoard() {
	for(int i = 0; i < H; i++) {
		for(int j = 0; j < H; j++) {
			if(board[i][j])	continue;
			int r = rand()%10000;
			if(r < 1024)
				board[i][j] = 2;
		}
	}
}

int* tBoard(int i, int j, int dir) {
	if(dir < 2)
		return &board[i][j];
	else
		return &board[j][i];
}
void moveBoard(int dir) { 
	int dx[] = {1, -1, 1, -1};
	for(int i = 0; i < H; i++) {
		int pos = dir%2 == 1 ? H-1 : 0;
		int stkpos = pos, stkcnt = 0, stktop;
		for(int j = pos, k = 0; k < H; j += dx[dir], k++) {
			if(*tBoard(j, i, dir) < 1) 
				continue;
			if(stkcnt == 0)	stkcnt = 1, stktop = *tBoard(j, i, dir);
			else {
				if(*tBoard(j, i, dir) == stktop)
					*tBoard(stkpos, i, dir) = stktop << 1, stkcnt = 0;
				else
					*tBoard(stkpos, i, dir) = stktop;
				stkpos += dx[dir], stktop = *tBoard(j, i, dir);
			}
		}
		if(stkcnt == 1)	*tBoard(stkpos, i, dir) = stktop, stkpos += dx[dir];
		while(stkpos >= 0 && stkpos < H) {
			*tBoard(stkpos, i, dir) = 0;
			stkpos += dx[dir];
		}
	}
} 
int main() {
	srand ( time(NULL));
	memset(board, 0, sizeof(board));
	char c;
	generateBoard();
	printBoard();
	while(c = getch()) {
		system("CLS");
		if(c == 'w' || c == 'W')
			moveBoard(0);
		if(c == 's' || c == 'S')
			moveBoard(1);
		if(c == 'a' || c == 'A')
			moveBoard(2);
		if(c == 'd' || c == 'D')
			moveBoard(3);
		generateBoard();
		printBoard();
	}
	return 0;
}
