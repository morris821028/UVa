#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;

#include "node.h"
#include "heap.h"

class MazeBoard {
    public:
        static const int LENG_LIMIT = 100;

        MazeBoard();
        MazeBoard(int, int, Node, Node);

        int build();

    protected:
        Node start;
        Node goal;

        void setRow(int);
        int getRow();
        void setColumn(int);
        int getColumn();
        void setStart(Node);
        void setGoal(Node);
        void setPoint(Node);
        bool isLegal(Node);
        bool isLegal(int, int);
        bool isEmptyPoint(Node);
        bool isEmptyPoint(int, int);
        bool isPoint(Node);
        bool isPoint(int, int);
        bool isWall(Node);
        bool isWall(int, int);
        void setWall(Node);
        void setWall(int, int);
		bool beVisited(Node);
		int getStep(Node);
		void setStep(Node, int);
		int getBestStep(Node);
		void setBestStep(Node, int);

    private:
        int row;
        int column;
        int board[LENG_LIMIT+2][LENG_LIMIT+2];
        int step[LENG_LIMIT+2][LENG_LIMIT+2];
        int best_route[LENG_LIMIT+2][LENG_LIMIT+2];

        void iniBoard();
        void genBoard();
        bool findRoute();
        void visit(Node, Node, Heap&);
        int absolute(int);
        int heuristic(Node);
        void findBestRoute();
        void save();
        void load();
};

class GameBoard : public MazeBoard {
    private:
        HANDLE hIn;
        HANDLE hOut;

        bool setIsDone;
        int player_route[MazeBoard::LENG_LIMIT+2][MazeBoard::LENG_LIMIT+2];

        void gotoxy(int, int);
        void draw(int, int, char*, int, int);
        Node getPoint(int);
        void giveMessage(char*);
        void lightAround(Node);
        void iniScreen();
        void walk(Node&);
        int getDireFromKeyBoard();
        bool isPlayAgain();
    public:

        GameBoard() {
            hIn = GetStdHandle(STD_INPUT_HANDLE);
            hOut = GetStdHandle(STD_OUTPUT_HANDLE);

            setIsDone = false;
        }

        void intro();
        int play();
        void printBestRoute();
        void quit();
};

#endif // BOARD_H_INCLUDED
