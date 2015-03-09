#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
HANDLE hIn, hOut;   //I/O 控制器
//游標控制 
void gotoxy (int x, int y) {
    static COORD c; c.X = y; c.Y = x;
    SetConsoleCursorPosition (hOut, c);
}
main() {
    hOut = GetStdHandle (STD_OUTPUT_HANDLE);
    hIn  = GetStdHandle (STD_INPUT_HANDLE);
    HANDLE err = INVALID_HANDLE_VALUE;
	gotoxy(10, 10);
	printf("haha =============>");
	gotoxy(8, 9);
	printf("<============= yoyo");
	gotoxy(23, 50);
	system("pause");
}
