#include <stdio.h>
#include <string.h>
#include <windows.h>
HANDLE hIn, hOut;
void gotoxy (int x, int y) {
    static COORD c; c.X = y; c.Y = x;
    SetConsoleCursorPosition (hOut, c);
}
void showText(int row, char text[], int len) {
    int i, j, wait  = 5;
    for(i = len-1; i >= 0; i--) {
        wait = 250/(i+1);
        if(text[i] == ' ')
            continue;
        for(j = 0; j <= i; j++) {
            gotoxy(row, j);
            putchar(' ');
            gotoxy(row, j+1);
            putchar(text[i]);
            Sleep(wait);
        }
    }
    Sleep(100);
}
int main() {
    hOut = GetStdHandle (STD_OUTPUT_HANDLE);
    hIn  = GetStdHandle (STD_INPUT_HANDLE);
    HANDLE err = INVALID_HANDLE_VALUE;
    char song[][100] = {
        "I walked ten thousnad miles, ten thousands miles to reach you",
        "   And every gasp of breath, I grabbed it just to find you",
        "           I climbed up every hill to get to you",
        "         I wandered ancient lands to hold just you",
        "",
        "          And every single step of the way, I paid",
        "        Every single night and day I searched for you",
        "      Through sand storms and hazy dawns I reached for you"
    };
    int i;
    for(i = 0; i < 8; i++) {
        showText(i, song[i], strlen(song[i]));
    }
    puts("");
    return 0;
}
