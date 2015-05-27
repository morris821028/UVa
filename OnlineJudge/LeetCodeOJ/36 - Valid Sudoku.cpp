#include <stdio.h>
#include <vector>
#include <ctype.h>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector< vector<char> >& board) {
        int mark[3][10][10] = {};
        for (int i = 0; i < 9; i++) {
        	for (int j = 0; j < 9; j++) {
        		if (isdigit(board[i][j])) {
        			int v = board[i][j] - '0';
        			int px = i/3, py = j/3;
        			if (mark[0][i][v] || mark[1][j][v] || mark[2][px*3+py][v])	
						return false;
					mark[0][i][v] = mark[1][j][v] = mark[2][px*3+py][v] = 1;
        		}
        	}
        }
        return true;
    }
};
int main() {
	return 0;
}
