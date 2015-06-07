#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int Y[32], usedY[32];
    void store(int n, vector< vector<string> > &ret) {
        string s(n, '.');
        vector<string> board;
        for (int i = 0; i < n; i++) {
            s[Y[i]] = 'Q';
            board.push_back(s);
            s[Y[i]] = '.';
        }
        ret.push_back(board);
    }
    int isValid(int x, int y) {
        if (usedY[y])   return 0;
        for (int i = 0; i < x; i++) {
            if (abs(Y[i] - y) == abs(x - i))
                return 0;
        }
        return 1;
    }
    void dfs(int idx, int n, vector< vector<string> > &ret) {
        if (idx == n) {
            store(n, ret);
            return ;
        }
        for (int i = 0; i < n; i++) {
            if (isValid(idx, i)) {
                Y[idx] = i;
                usedY[i] = 1;
                dfs(idx+1, n, ret);
                usedY[i] = 0;
            }
        }
    }
    vector< vector<string> > solveNQueens(int n) {
        memset(usedY, 0, sizeof(usedY));
        vector< vector<string> > ret;
        dfs(0, n, ret);
        return ret;
    }
};

int main() {
    Solution s;
    vector< vector<string> > ret = s.solveNQueens(8);
    cout << ret.size() << endl;
    return 0;
}