#include <stdio.h>
#include <queue>
using namespace std;
char mark[1<<18] = {}, ans[1<<18], best[1<<18];
char dirp[4] = {-3, 1, 1, 1};
int next[1<<18] = {};
int pow4[10] = {1};
int move[10][7] = { {},
                 	{1, 2, 4, 5, 0},
                 	{1, 2, 3, 0},
                 	{2, 3, 5, 6, 0},
                 	{1, 4, 7, 0},
                 	{2, 4, 5, 6, 8, 0},
                 	{3, 6, 9, 0},
                 	{4, 5, 7, 8, 0},
                 	{7, 8, 9, 0},
                 	{5, 6, 8, 9, 0}
                   };
void trans(int N, char s[]) {
	int i = 0;
    while(N) {
        s[i++] = N%4, N /= 4;
    }
}
void build() {
    int a, b, c, qt = 0, t, p;
    queue<int> Q;
    best[0] = 0, mark[0] = 1;
    Q.push(0);
    while(!Q.empty()) {
    	int state = Q.front();
    	Q.pop();
    	char buf[10] = {};
    	trans(state, buf);
    	for(int i = 1; i < 10; i++) {
    		int nstate = state;
    		for(int j = 0; move[i][j]; j++)
    			nstate -= pow4[move[i][j] - 1] * dirp[buf[move[i][j] - 1]];
    		if(mark[nstate] == 0) {
    			mark[nstate] = 1;
    			next[nstate] = state;
				best[nstate] = best[state] + 1;
				ans[nstate] = i + '0';
    			Q.push(nstate);
    		}
    	}
    }
}
int print_f = 0;
void Print(int state) {
    if(state) {
        Print(next[state]);
        if(print_f)
			putchar(' ');
        print_f = 1;
        putchar(ans[state]);
    }
}
int main() {
    for(int i = 1; i < 10; i++)
        pow4[i] = pow4[i-1] * 4;
    build();
    while(true) {
    	int state = 0, x;
        for(int i = 0; i < 9; i++) {
            if(scanf("%d", &x) != 1)
            	return 0;
            state |= x * pow4[i];
        }
        print_f = 0;
        Print(state);
		puts("");
    }
    return 0;
}  
