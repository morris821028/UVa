#include <bits/stdc++.h>
using namespace std;

const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};
char g[16][16], s[256];
void printLegal(int turn) {
	int first = 0;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (g[i][j] != '-')
				continue;
			int valid = 0;
            for (int k = 0; k < 8; k++) {
                int x = i + dx[k], y = j + dy[k];
                int cnt = 0, ok = 0;
                while (x >= 1 && x <= 8 && y >= 1 && y <= 8) {
                    if (g[x][y] == '-')	break;
                    if (g[x][y] == 'W' && turn == 0) {
						ok = 1;
						break;
					}
                    if (g[x][y] == 'B' && turn == 1) {
						ok = 1;
						break;
					}
					cnt++;
                    x += dx[k], y += dy[k];
                }
                if (ok == 1 && cnt >= 1) {
                	valid = 1;
                	break;
                }
            }
            if (valid == 1) {
                if (first)   putchar(' ');
                first = 1;
                printf("(%d,%d)", i, j);
            }
        }
    }
    if (!first)
		puts("No legal move.");
    else
		puts("");
}
int WTFhasNext(int turn) {	// why not check only ...
	for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (g[i][j] != '-')
				continue;
			int valid = 0;
            for (int k = 0; k < 8; k++) {
                int x = i + dx[k], y = j + dy[k];
                int cnt = 0, ok = 0;
                while (x >= 1 && x <= 8 && y >= 1 && y <= 8) {
                    if (g[x][y] == '-')	break;
                    if (g[x][y] == 'W' && turn == 0) {
						ok = 1;
						break;
					}
                    if (g[x][y] == 'B' && turn == 1) {
						ok = 1;
						break;
					}
					cnt++;
                    x += dx[k], y += dy[k];
                }
                if (ok == 1 && cnt >= 1) {
                	valid = 1;
                	break;
                }
            }
            if (valid == 1)
                return 1;
        }
    }
	return 0;
}
void move(char s[], int &turn) {
	int test = 0;
    if (WTFhasNext(turn) == 0)
    	turn = !turn;
    int x = s[1]-'0', y = s[2]-'0';
    g[x][y] = turn ? 'B' : 'W';
    int valid = 0;
    for (int i = 0; i < 8; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        int cnt = 0, ok = 0;
        while (tx >= 1 && tx <= 8 && ty >= 1 && ty <= 8) {
            if(g[tx][ty] == '-')
                break;
            if (g[tx][ty] == 'W' && turn == 0) {
				ok = 1;
				break;
			}
            if (g[tx][ty] == 'B' && turn == 1) {
                ok = 1;
				break;
			}
            cnt++;
            tx += dx[i], ty += dy[i];
        }
        if (ok == 1 && cnt >= 1) {
            valid = 1;
            tx = x + dx[i], ty = y + dy[i];
            while (tx >= 1 && tx <= 8 && ty >= 1 && ty <= 8) {
                if (g[tx][ty] == '-')
                    break;
                if (g[tx][ty] == 'W' && turn == 0)
                    break;
                if (g[tx][ty] == 'B' && turn == 1)
                    break;
                g[tx][ty] = turn ? 'B' : 'W';
                tx += dx[i], ty += dy[i];
            }
        }
    }
    turn = !turn;
    int W = 0, B = 0;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (g[i][j] == 'B')  B++;
            if (g[i][j] == 'W')  W++;
        }
    }
    printf("Black - %2d White - %2d\n", B, W);
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        for(int i = 1; i <= 8; i++)
            scanf("%s", g[i]+1);
        scanf("%s", s);
        int turn = s[0] == 'B';
        while (scanf("%s", s) == 1) {
            if (s[0] == 'Q')
                break;
            if (s[0] == 'L') {
                printLegal(turn);
            } else {
            	move(s, turn);
			}
        }
        for (int i = 1; i <= 8; i++, puts(""))
            for (int j = 1; j <= 8; j++)
                putchar(g[i][j]);
        if (testcase)
            puts("");
    }
    return 0;
}
