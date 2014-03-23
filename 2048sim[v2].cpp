#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <conio.h> 
#include <time.h>
#include <windows.h>
#include <math.h> 
#include <algorithm>
using namespace std;
//mutex class
class Mutex
{
public:
    //the default constructor
    Mutex()
    {
        InitializeCriticalSection(&m_criticalSection);
    }

    //destructor
    ~Mutex()
    {
        DeleteCriticalSection(&m_criticalSection);
    }

    //lock
    void lock()
    {
        EnterCriticalSection(&m_criticalSection);
    }

    //unlock
    void unlock()
    {
        LeaveCriticalSection(&m_criticalSection);
    }

private:
    CRITICAL_SECTION m_criticalSection;
};

//synchronization controller object
class Lock
{
public:
    //the default constructor
    Lock(Mutex &mutex) : m_mutex(mutex), m_locked(true)
    {
        mutex.lock();
    }

    //the destructor
    ~Lock()
    {
        m_mutex.unlock();
    }

    //report the state of locking when used as a boolean
    operator bool () const
    {
        return m_locked;
    }

    //unlock
    void setUnlock()
    {
        m_locked = false;        
    }

private:
    Mutex &m_mutex;
    bool m_locked;
};
#define synchronized(M)  for(Lock M##_lock = M; M##_lock; M##_lock.setUnlock())
//mutex
Mutex mutex1, mutex2;

#define MAX_THREADS 32

typedef struct MyData{
	int row, col, val;
	int mr, mc, mv;
	int px, py, fx, fy, bx, by;
} *PMYDATA, MYDATA;		

DWORD   dwThreadIdArray[MAX_THREADS];
PMYDATA pDataArray[MAX_THREADS];
HANDLE  hThreadArray[MAX_THREADS]; 

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hIn = GetStdHandle (STD_INPUT_HANDLE);
HANDLE hOut = GetStdHandle (STD_OUTPUT_HANDLE);
HANDLE err = INVALID_HANDLE_VALUE;

inline void gotoxy (int x, int y) {
    COORD c; c.X = y; c.Y = x;
    SetConsoleCursorPosition (hOut, c);
}
inline void printCell(int row, int col, int val) {
	int bx, by;
	bx = row * 4, by = col * 6;
	gotoxy(bx, by);	
	SetConsoleTextAttribute(hConsole, 15);
	if(val > 0)
		SetConsoleTextAttribute(hConsole, ((int)(log2(val)))%6 + 10);
	synchronized(mutex1)
    {
		printf("======"), gotoxy(bx + 1, by);
		printf("|    |"), gotoxy(bx + 2, by);
		if(val > 0)
			printf("|%4d|", val), gotoxy(bx + 3, by);
		else
			printf("|    |"), gotoxy(bx + 3, by);		
		printf("|    |"), gotoxy(bx + 4, by);
		printf("======"), gotoxy(bx + 5, by);
	}
	Sleep(20);
}
const int H = 5;
int board[H][H];
void repeatPrint(char str[], int n) {
	while(n--)	printf(str);
	puts("");
	Sleep(20);
}

void printAnimation(LPVOID lpParam) {
    PMYDATA pDataArray;
    pDataArray = (PMYDATA)lpParam;
	int &row = pDataArray->row;
	int &col = pDataArray->col;
	int &val = pDataArray->val;
	int &mr = pDataArray->mr;
	int &mc = pDataArray->mc;
	int &mv = pDataArray->mv;
	int &bx = pDataArray->bx;
	int &by = pDataArray->by;
	int &px = pDataArray->px;
	int &py = pDataArray->py;
	int &fx = pDataArray->fx;
	int &fy = pDataArray->fy;
	bx = row * 4;
	by = col * 6;
	px = bx;
	py = by;
	fx = mr * 4, fy = mc * 6;
	do {    		
		synchronized(mutex2)
    	{	
			HANDLE hStdout;    
			hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	    	if( hStdout == INVALID_HANDLE_VALUE )
	    		continue;
			if(bx == fx && by == fy) { 
			} else {
				if(bx == fx)
					by += by < fy ? 1 : -1;
				else
					bx += bx < fx ? 1 : -1;
			}
			if(bx == fx && by == fy)
				val = mv;
			gotoxy(bx, by);	
			SetConsoleTextAttribute(hConsole, 15);
			if(val > 0)
				SetConsoleTextAttribute(hConsole, ((int)(log2(val)))%6 + 10);
			printf("======"), gotoxy(bx + 1, by);
			printf("|    |"), gotoxy(bx + 2, by);
			if(val > 0)
				printf("|%4d|", val), gotoxy(bx + 3, by);
			else
				printf("|    |"), gotoxy(bx + 3, by);		
			printf("|    |"), gotoxy(bx + 4, by);
			printf("======"), gotoxy(bx + 5, by);
			Sleep(50 - max(abs(bx - fx), abs(by - fy))*2);
			px = bx, py = by;
		}
	} while(bx != fx || by != fy);
}

void buildThread(int index, int row, int col, int val, 
				int mr, int mc, int mv) {
	if(row == mr && col == mc)
		return;
	pDataArray[index] = (PMYDATA) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                sizeof(MYDATA));
    pDataArray[index]->row = row;
    pDataArray[index]->col = col;
    pDataArray[index]->val = val;
    pDataArray[index]->mr = mr;
    pDataArray[index]->mc = mc;
    pDataArray[index]->mv = mv;
    
    hThreadArray[index] = CreateThread( 
            NULL,                   	// default security attributes
            10,                      	// use default stack size  
            (LPTHREAD_START_ROUTINE)printAnimation, // thread function name
            pDataArray[index],          // argument to thread function 
            0,                      	// use default creation flags 
            &dwThreadIdArray[index]);   // returns the thread identifier 
    if (hThreadArray[index] == NULL) {
    	ExitProcess(3);
    }
}
void printBoard() {
	for(int i = 0; i < H; i++)
		for(int j = 0; j < H; j++)
			printCell(i, j, board[i][j]);
	//repeatPrint("======", H);
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
	int prevx = 0;
	for(int i = 0; i < H; i++) {
		int pos = dir%2 == 1 ? H-1 : 0;
		int stkpos = pos, stkcnt = 0, stktop;
		for(int j = pos, k = 0; k < H; j += dx[dir], k++) {
			if(*tBoard(j, i, dir) < 1) 
				continue;
			prevx = j;
			if(stkcnt == 0)	stkcnt = 1, stktop = *tBoard(j, i, dir);
			else {
				if(*tBoard(j, i, dir) == stktop) {
					if(dir < 2)
						buildThread(i*H + j, j, i, stktop, stkpos, i, stktop<<1);
					else
						buildThread(i*H + j, i, j, stktop, i, stkpos, stktop<<1);
					*tBoard(stkpos, i, dir) = stktop << 1, stkcnt = 0;
					//Sleep(50);
				} else {
					if(dir < 2)
						buildThread(i*H + j, prevx, i, stktop, stkpos, i, stktop);
					else
						buildThread(i*H + j, i, prevx, stktop, i, stkpos, stktop);
					*tBoard(stkpos, i, dir) = stktop;
					//Sleep(30);
				}
				stkpos += dx[dir], stktop = *tBoard(j, i, dir);
			}
		}
		if(stkcnt == 1)	{
			if(dir < 2)
				buildThread(i*H + H-1, prevx, i, stktop, stkpos, i, stktop);
			else
				buildThread(i*H + H-1, i, prevx, stktop, i, stkpos, stktop);
			*tBoard(stkpos, i, dir) = stktop, stkpos += dx[dir];
			//Sleep(30);
		}
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
		//system("CLS");
		if(c == 'w' || c == 'W')
			moveBoard(0);
		if(c == 's' || c == 'S')
			moveBoard(1);
		if(c == 'a' || c == 'A')
			moveBoard(2);
		if(c == 'd' || c == 'D')
			moveBoard(3);
		generateBoard();
	}
	return 0;
}
