#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "board.h"
#include "node.h"

using namespace std;

#define BLANK 0
#define YELLOW_FORE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define GREEN_FORE FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define WHITE_FORE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define LIGHTWHITE_FORE FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define GREEN_BACK BACKGROUND_GREEN
#define WHITE_BACK BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
#define YELLOW_BACK BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY

MazeBoard::MazeBoard() {}

MazeBoard::MazeBoard(int n, int m, Node a, Node b) {
    row = n;
    column = m;

    start = a;
    goal = b;
}

void MazeBoard::setRow(int n) {
    row = n;
}

int MazeBoard::getRow() {
    return row;
}

void MazeBoard::setColumn(int n) {
    column = n;
}

int MazeBoard::getColumn() {
    return column;
}

void MazeBoard::setStart(Node node) {
    start = node;
    setPoint(start);
}

void MazeBoard::setGoal(Node node) {
    goal = node;
    setPoint(goal);
}

void MazeBoard::setPoint(Node node) {
    board[node.x][node.y] = 1;
}

bool MazeBoard::isLegal(Node node) {
    return isLegal(node.x, node.y);
}

bool MazeBoard::isLegal(int x, int y) {
    return x >= 1 && x <= row && y >= 1 && y <= column;
}

bool MazeBoard::isEmptyPoint(Node node) {
    return isEmptyPoint(node.x, node.y);
}

bool MazeBoard::isEmptyPoint(int x, int y) {
    if(isLegal(x, y) == true)
        return board[x][y] == 0;
    else
        return false;
}

bool MazeBoard::isPoint(Node node) {
    return isPoint(node.x, node.y);
}

bool MazeBoard::isPoint(int x, int y) {
    return board[x][y] == 1;
}

bool MazeBoard::isWall(Node node) {
    return isWall(node.x, node.y);
}

bool MazeBoard::isWall(int x, int y) {
    return board[x][y] == -1;
}

void MazeBoard::setWall(Node node) {
    setWall(node.x, node.y);
}

void MazeBoard::setWall(int x, int y) {
    if(isEmptyPoint(x, y) == true)
        board[x][y] = -1;
}

bool MazeBoard::beVisited(Node node) {
    return step[node.x][node.y] > 0;
}

int MazeBoard::getStep(Node node) {
    return step[node.x][node.y];
}

void MazeBoard::setStep(Node node, int s) {
    step[node.x][node.y] = s;
}

int MazeBoard::getBestStep(Node node) {
    return best_route[node.x][node.y];
}

void MazeBoard::setBestStep(Node node, int s) {
    best_route[node.x][node.y] = s;
}

void MazeBoard::iniBoard() {
    for(int i = 0; i <= row+1; i++)
        board[i][0] = board[i][column+1] = -1;

    for(int i = 0; i <= column+1; i++)
        board[0][i] = board[row+1][i] = -1;

    for(int i = 1; i <= row; i++)
        for(int j = 1; j <= column; j++)
            board[i][j] = 0;

    for(int i = 0; i <= row+1; i++)
        for(int j = 0; j <= column+1; j++)
            step[i][j] = best_route[i][j];

    board[start.x][start.y] = 1;
    board[goal.x][goal.y] = 1;
}

void MazeBoard::genBoard() {
    iniBoard();

    srand(time(NULL));

    for(int i = 0; i < row*column/5; i++) {
        Node new_wall(rand()%row+1, rand()%column+1);

        int length = rand()%(row*column/30);

        for(int j = 0; j < length; j++) {
            if(isEmptyPoint(new_wall) == false)
                continue;

            setWall(new_wall);

            switch(rand()%4+1) {
                case 1:
                    if(isEmptyPoint(new_wall.up()) == true&&isEmptyPoint(new_wall.up().up()) == true)
                        new_wall = new_wall.up();
                    break;
                case 2:
                    if(isEmptyPoint(new_wall.down()) == true&&isEmptyPoint(new_wall.down().down()) == true)
                        new_wall = new_wall.down();
                    break;
                case 3:
                    if(isEmptyPoint(new_wall.right()) == true&&isEmptyPoint(new_wall.right().right()) == true)
                        new_wall = new_wall.right();
                    break;
                case 4:
                    if(isEmptyPoint(new_wall.left()) == true&&isEmptyPoint(new_wall.left().left()) == true)
                        new_wall = new_wall.left();
                    break;
            }
        }
    }

    for(int i = 1; i <= row; i++)
        for(int j = 1; j <= column; j++)
            if(isEmptyPoint(i+1, j+1) == true&&isEmptyPoint(i-1, j+1) == true&&isEmptyPoint(i-1, j-1) == true&&isEmptyPoint(i+1, j-1) == true)
                setWall(i, j);

    for(int i = 0; i < row/3; i++) {
        setWall(rand()%row+1, 1);
        setWall(rand()%row+1, column);
    }

    for(int i = 0; i < column/3; i++) {
        setWall(1, rand()%column+1);
        setWall(row, rand()%column+1);
    }
}

bool MazeBoard::findRoute() {
    Heap openList;

	openList.insert(start);
	while(openList.isEmpty() == false) {
		Node curr(openList.remove());

		if(curr == goal)
			break;

		visit(curr, curr.up(), openList);
		visit(curr, curr.down(), openList);
		visit(curr, curr.right(), openList);
		visit(curr, curr.left(), openList);
	}

    setStep(start, 0);
    return getStep(goal)-!beVisited(goal) != -1;
}

void MazeBoard::visit(Node curr, Node next, Heap& openList) {
    if(isWall(next) == true)
        return ;

	if(getStep(next) > getStep(curr)+1 || beVisited(next) == false) {
		setStep(next, getStep(curr)+1);

		next.f = getStep(next)*row*column+heuristic(next);
		openList.insert(next);
	}
}

int MazeBoard::absolute(int n) {
    return n >= 0?n:-n;
}

int MazeBoard::heuristic(Node current) {
	int dx1 = current.x-goal.x;
	int dy1 = current.y-goal.y;
	int dx2 = start.x-goal.x;
	int dy2 = start.y-goal.y;

	return absolute(dx1*dy2-dx2*dy1)+(absolute(dx1)+absolute(dy1))*row*column;
}

void MazeBoard::findBestRoute() {
    Node curr(goal);

    while(curr != start) {
        setBestStep(curr, getStep(curr));

        if(getBestStep(curr)-1 == getStep(curr.up())&&isWall(curr.up()) == false)
            curr = curr.up();
        else if(getBestStep(curr)-1 == getStep(curr.down())&&isWall(curr.down()) == false)
            curr = curr.down();
        else if(getBestStep(curr)-1 == getStep(curr.right())&&isWall(curr.right()) == false)
            curr = curr.right();
        else if(getBestStep(curr)-1 == getStep(curr.left())&&isWall(curr.left()) == false)
            curr = curr.left();
    }
}

void MazeBoard::save() {
    FILE* fp = fopen("maze.txt", "w");

    for(int i = 0; i <= row+1; i++) {
        for(int j = 0; j <= column+1; j++)
            fprintf(fp, "%3d", board[i][j]);

        fprintf(fp, "\n");
    }

    for(int i = 0; i <= row+1; i++) {
        for(int j = 0; j <= column+1; j++)
            fprintf(fp, "%3d", best_route[i][j]);

        fprintf(fp, "\n");
    }

    fclose(fp);
}

void MazeBoard::load() {
    FILE* fp = fopen("maze.txt", "r");

    for(int i = 0; i <= row+1; i++)
        for(int j = 0; j <= column+1; j++)
            fscanf(fp, "%d", &board[i][j]);

    for(int i = 0; i <= row+1; i++)
        for(int j = 0; j <= column+1; j++)
            fscanf(fp, "%d", &best_route[i][j]);

    fclose(fp);
}

int MazeBoard::build() {
    int cnt;

    cnt = 0;
    do {
        genBoard();
        cnt += 1;
    } while(findRoute() == false);

    findBestRoute();

    save();

    return cnt;
}

void GameBoard::intro() {
    int a, b;

    draw(1, 1, "Maze Game", YELLOW_FORE, 1);

    draw(3, 1, "Please enter Row and Column of the Maze (20*20 ~ 50*50)", GREEN_FORE, 1);
    do {
        draw(4, 1, "                                                       ", BLANK, 1);
        draw(5, 1, "                                                       ", BLANK, 1);

        draw(4, 1, "Row:", GREEN_FORE, 1);
        draw(4, 5, " ", WHITE_FORE, 1);
        cin>>a;
        setRow(a);

        draw(5, 1, "Column:", GREEN_FORE, 1);
        draw(5, 5, " ", WHITE_FORE, 1);
        cin>>b;
        setColumn(b);

    } while(getRow() < 20 || getRow() > 50 || getColumn() < 20 || getColumn() > 50);

    iniScreen();

    giveMessage("Use UP, DOWN, LEFT, RIGHT to set START, and press ENTER");
    setStart(getPoint(0));

    giveMessage("Use UP, DOWN, LEFT, RIGHT to set GOAL, and press ENTER");
    setGoal(getPoint(1));

    setIsDone = true;

    giveMessage("Maze is generating...");
}

void GameBoard::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hOut, coord);
}

void GameBoard::draw(int x, int y, char *msg, int color, int spe = 0) {
    if(isLegal(x, y) == false && isWall(x, y) == false && spe == 0)
        return ;

    SetConsoleTextAttribute(hOut, color);
    gotoxy(2*(y+1), x+1);

    cout<<msg;
}

Node GameBoard::getPoint(int point) {
    const int default_place[2][2] = {{1, 1}, {getRow(), getColumn()}};
    Node tmp(default_place[point][0], default_place[point][1]);

    while(1) {
        draw(tmp.x, tmp.y, "£K", YELLOW_FORE);

        switch(getDireFromKeyBoard()) {
            case 0:
                return tmp;
            case 1:
                if(isLegal(tmp.up()) == true && isPoint(tmp.up()) == false) {
                    draw(tmp.x, tmp.y, "  ", BLANK);
                    tmp = tmp.up();
                }
                break;
            case 2:
                if(isLegal(tmp.down()) == true && isPoint(tmp.down()) == false) {
                    draw(tmp.x, tmp.y, "  ", BLANK);
                    tmp = tmp.down();
                }
                break;
            case 3:
                if(isLegal(tmp.left()) == true && isPoint(tmp.left()) == false) {
                    draw(tmp.x, tmp.y, "  ", BLANK);
                    tmp = tmp.left();
                }
                break;
            case 4:
                if(isLegal(tmp.right()) == true && isPoint(tmp.right()) == false) {
                    draw(tmp.x, tmp.y, "  ", BLANK);
                    tmp = tmp.right();
                }
                break;
        }
    }

    return 0;
}

void GameBoard::giveMessage(char* msg) {
    draw(getRow()+3, 1, "                                                       ", LIGHTWHITE_FORE, 1);
    draw(getRow()+3, 1, msg, LIGHTWHITE_FORE, 1);
}

void GameBoard::lightAround(Node node) {
    int dire[5] = {-2, -1, 0, 1, 2};

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(dire[i] == 0 && dire[j] == 0)
                draw(node.x, node.y, "£K", GREEN_FORE);
            else if(isWall(node.x+dire[i], node.y+dire[j]) == true)
                draw(node.x+dire[i], node.y+dire[j], "  ", WHITE_BACK);
            else if(isPoint(node.x+dire[i], node.y+dire[j]) == true)
                draw(node.x+dire[i], node.y+dire[j], "£K", YELLOW_FORE);
            else
                draw(node.x+dire[i], node.y+dire[j], "  ", BLANK);
        }
    }
}

void GameBoard::walk(Node& curr) {
    switch(getDireFromKeyBoard()) {
        case 1:
            if(isWall(curr.up()) == false)
                curr = curr.up();
            break;
        case 2:
            if(isWall(curr.down()) == false)
                curr = curr.down();
            break;
        case 3:
            if(isWall(curr.left()) == false)
                curr = curr.left();
            break;
        case 4:
            if(isWall(curr.right()) == false)
                curr = curr.right();
            break;
    }

    player_route[curr.x][curr.y] = 1;
}

int GameBoard::getDireFromKeyBoard() {
    switch((char)getch()) {
        case 13: // enter
            return 0;
        case -32:
            switch((char)getch()) {
                case 72:
                    return 1; // up
                case 80:
                    return 2; // down
                case 75:
                    return 3; // left
                case 77:
                    return 4; // right
            }
        default:
            return -1;
    }
}

bool GameBoard::isPlayAgain() {
    char ch;

    draw(getRow()+5, 1, "Play again? n/y ", LIGHTWHITE_FORE, 1);
    cin>>ch;

    draw(getRow()+5, 1, "                   ", LIGHTWHITE_FORE, 1);
    return ch == 'y';
}

// http://ascii-table.com/ascii-extended-pc-list.php
int GameBoard::play() {
    iniScreen();

    giveMessage("Playing...");

    Node curr(start);
    lightAround(start);

    clock_t start_t = clock();
    while(curr != goal) {
        walk(curr);
        lightAround(curr);
    }
    clock_t end_t = clock();

    // print cost time
    giveMessage("Congratulation!!! The time you spent: ");
    cout<<(end_t-start_t)/(double)(CLOCKS_PER_SEC)<<"s";

    return isPlayAgain();
}

void GameBoard::iniScreen() {
    system("cls");

    for(int i = 0; i <= getRow()+1; i++) {
        for(int j = 0; j <= getColumn()+1; j++) {
            if(i == 0 || i == getRow()+1 || j == 0 || j == getColumn()+1)
                draw(i, j, "  ", WHITE_BACK, 1);
            else
                draw(i, j, "  ", BLANK, 1);
        }
    }

    if(setIsDone == true) {
        draw(start.x, start.y, "£K", YELLOW_FORE);
        draw(goal.x, goal.y, "£K", YELLOW_FORE);
    }
}

void GameBoard::printBestRoute() {
    giveMessage("GREEN: your route      YELLOW: best route");

    for(int i = 1; i <= getRow(); i++)
        for(int j = 1; j <= getColumn(); j++) {
            if(isWall(i, j) == true)
                draw(i, j, "  ", WHITE_BACK);

            if(player_route[i][j] == 1 && isPoint(i, j) == false)
                draw(i, j, "  ", GREEN_BACK);
        }

    Node curr(start);
    do {
        if(curr != start && curr != goal)
            draw(curr.x, curr.y, "  ", YELLOW_BACK);

        if(getBestStep(curr.up()) == getBestStep(curr)+1)
            curr = curr.up();
        else if(getBestStep(curr.down()) == getBestStep(curr)+1)
            curr = curr.down();
        else if(getBestStep(curr.left()) == getBestStep(curr)+1)
            curr = curr.left();
        else if(getBestStep(curr.right()) == getBestStep(curr)+1)
            curr = curr.right();

        Sleep(80);
    } while(curr != goal);
}

void GameBoard::quit() {
    draw(getRow()+5, 1, "the end.", YELLOW_FORE, 1);
    draw(getRow()+7, 1, "Press any key to leave...", WHITE_FORE, 1);

    getch();
}

