#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
HANDLE hIn, hOut, hConsole;
void gotoxy (int x, int y) {
    static COORD c; c.X = y; c.Y = x;
    SetConsoleCursorPosition (hOut, c);
}
struct {
	char s[100];
	int sx, sy, ex, sL;
	int up_down, set[100];
	int color, changecolor, changeset, exceed;
}Code[100];
main() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hOut = GetStdHandle (STD_OUTPUT_HANDLE);
    hIn  = GetStdHandle (STD_INPUT_HANDLE);
    HANDLE err = INVALID_HANDLE_VALUE;
    srand ( time(NULL));
    int map[24][79] = {0}, a, b;
    int up_down, sx = -1, sy = 0, ex, sL, space;
    int ASCII[63], ASCidx = 0;
    for(a = '0'; a <= '9'; a++)
    	ASCII[ASCidx++] = a;
    for(a = 'a'; a <= 'z'; a++)
    	ASCII[ASCidx++] = a;
    for(a = 'A'; a <= 'Z'; a++)
    	ASCII[ASCidx++] = a;
    ASCidx = 2;
    for(a = 0; a < 39; a++) {
		for(b = 0; b < 100; b++)
			Code[a].s[b] = ASCII[rand()%ASCidx];
		sL = rand()%20+10;
		up_down = rand()%2;
		sx = 0, ex = 23;
		Code[a].sL = sL, Code[a].sx = sx, Code[a].ex = ex;
		Code[a].up_down = up_down, Code[a].sy = sy;
		if(up_down) {
			int i, st_time = rand()%50+1;
			for(i = 0; i < sL; i++)
				Code[a].set[i] = ex+i+st_time;
		} else {
			int i, st_time = rand()%50+1;
			for(i = 0; i < sL; i++)
				Code[a].set[i] = sx-i-st_time;
		}
		Code[a].color = rand()%2 ? 2 : 10;
		Code[a].changecolor = 0, Code[a].changeset = rand()%23;
		Code[a].exceed = 0;
		sy += 2;
	}
	int Order[1000], OL = 1000;
	int i, j;
    while(1) {
		for(a = 0; a < 39; a++) {
			if(Code[a].exceed == 1)
				SetConsoleTextAttribute(hConsole, Code[a].color == 2 ? 10 : 2);
			else
				SetConsoleTextAttribute(hConsole, Code[a].color);
			Code[a].changecolor ++;
			if(Code[a].up_down) {
				for(i = 0; i < Code[a].sL; i++) {
					if(Code[a].set[i] == Code[a].changeset) {
						Code[a].exceed = 1;
						SetConsoleTextAttribute(hConsole, Code[a].color);
					}
					/*if(Code[a].set[i] < Code[a].sx)
						Code[a].set[i] += (Code[a].ex-Code[a].sx), Code[a].s[i] = (rand()&1) + '0';*/
					if(Code[a].set[i] >= Code[a].sx && Code[a].set[i] <= Code[a].ex) {
						gotoxy(Code[a].set[i], Code[a].sy), printf("%c", Code[a].s[i]);
						if(Code[a].set[i] != Code[a].ex)
							gotoxy(Code[a].set[i]+1, Code[a].sy), printf(" ");
					}
					if(Code[a].set[i] == Code[a].sx)
						gotoxy(Code[a].sx, Code[a].sy), printf(" ");
					Code[a].set[i]--;
				}
			} else {
				for(i = 0; i < Code[a].sL; i++) {
					if(Code[a].set[i] == Code[a].changeset) {
						Code[a].exceed = 1;
						SetConsoleTextAttribute(hConsole, Code[a].color);
					}
					/*if(Code[a].set[i] > Code[a].ex)
						Code[a].set[i] -= (Code[a].ex-Code[a].sx), Code[a].s[i] = (rand()&1) + '0';*/
					if(Code[a].set[i] >= Code[a].sx && Code[a].set[i] <= Code[a].ex) {
						gotoxy(Code[a].set[i], Code[a].sy), printf("%c", Code[a].s[i]);
						if(Code[a].set[i] != Code[a].sx)
							gotoxy(Code[a].set[i]-1, Code[a].sy), printf(" ");
					} 
					if(Code[a].set[i] == Code[a].ex)
						gotoxy(Code[a].ex, Code[a].sy), printf(" ");
					Code[a].set[i]++;
				}
			}
			/*if(Code[a].set[Code[a].sL-1] < Code[a].sx && Code[a].up_down) {
				Code[a].sL = rand()%20 + 10;
				int st_time = rand()%10;
				for(i = 0; i < Code[a].sL; i++)
					Code[a].s[i] = rand()%2 ? '1' : '0', Code[a].set[i] = Code[a].ex+i+st_time;
				Code[a].changecolor = 0, Code[a].color = rand()%20 ? 10 : 2;
				Code[a].changeset = rand()%23, Code[a].exceed = 0;
			}
			if(Code[a].set[Code[a].sL-1] > Code[a].ex && Code[a].up_down == 0) {
				Code[a].sL = rand()%20 + 10;
				int st_time = rand()%10;
				for(i = 0; i < Code[a].sL; i++)
					Code[a].s[i] = rand()%2 ? '1' : '0', Code[a].set[i] = Code[a].sx-i-st_time;
				Code[a].changecolor = 0, Code[a].color = rand()%20 ? 10 : 2;
				Code[a].changeset = rand()%23, Code[a].exceed = 0;
			}*/ 
			if((Code[a].set[Code[a].sL-1] < Code[a].sx && Code[a].up_down) || (Code[a].set[Code[a].sL-1] > Code[a].ex && Code[a].up_down == 0)) {
				Code[a].up_down = rand()%2;
				if(Code[a].up_down) {
					Code[a].sL = rand()%20 + 10;
					int st_time = rand()%40;
					for(i = 0; i < Code[a].sL; i++)
						Code[a].s[i] = ASCII[rand()%ASCidx], Code[a].set[i] = Code[a].ex+i+st_time;
					Code[a].changecolor = 0, Code[a].color = rand()%20 ? 10 : 2;
					Code[a].changeset = rand()%23, Code[a].exceed = 0;
				} else {
					Code[a].sL = rand()%20 + 10;
					int st_time = rand()%40;
					for(i = 0; i < Code[a].sL; i++)
						Code[a].s[i] = ASCII[rand()%ASCidx], Code[a].set[i] = Code[a].sx-i-st_time;
					Code[a].changecolor = 0, Code[a].color = rand()%20 ? 10 : 2;
					Code[a].changeset = rand()%23, Code[a].exceed = 0;
				}
			}
		}		 
		Sleep(30);
	}
	gotoxy(23, 78);
	system("pause");
	return 0;
}
