#include <conio.h>

#include "board.h"

int main() {
    CONSOLE_CURSOR_INFO ConCurInf;

    SetConsoleTitle("Maze Game");
    ConCurInf.bVisible = FALSE;

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConCurInf);

    GameBoard maze;

    maze.intro();

    maze.build();

    while(maze.play());

    maze.printBestRoute();

    maze.quit();

    return 0;
}
