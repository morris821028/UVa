#include <stdio.h>
#include <vector>
#include <string.h>
#include <ctype.h>
using namespace std;

class Solution {
public:
	int mark[3][10][10];
	vector< pair<int, int> > A;
	int dfs(int idx, vector< vector<char> >& board) {
		if (idx == A.size())
			return 1;
		int x = A[idx].first, y = A[idx].second;
		for (int i = 1; i <= 9; i++) {
			board[x][y] = i + '0';
			if (mark[0][x][i] || mark[1][y][i] || mark[2][(x/3)*3+(y/3)][i])
				continue;
			mark[0][x][i] = mark[1][y][i] = mark[2][(x/3)*3+(y/3)][i] = 1;
			if (dfs(idx+1, board))
				return 1;
			mark[0][x][i] = mark[1][y][i] = mark[2][(x/3)*3+(y/3)][i] = 0;
		}
		return 0;
	}
    void solveSudoku(vector< vector<char> >& board) {
    	memset(mark, 0, sizeof(mark));
    	A.clear();
        for (int i = 0; i < 9; i++) {
        	for (int j = 0; j < 9; j++) {
        		if (isdigit(board[i][j])) {
        			int v = board[i][j] - '0';
        			int px = i/3, py = j/3;
					mark[0][i][v] = mark[1][j][v] = mark[2][px*3+py][v] = 1;
        		} else {
        			A.push_back(make_pair(i, j));
        		}
        	}
        }
        
        dfs(0, board);
    }
};
int main() {
	return 0;
}
