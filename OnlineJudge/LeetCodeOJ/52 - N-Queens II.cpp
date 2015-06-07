#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    void dfs(int row, int dia1, int dia2, int mask, int &cnt) {
        if (row == mask) {
            cnt++;
            return ;
        }
        
        int pos = mask & (~(row | dia1 | dia2)), p;
        while (pos) {
            p = pos & (-pos);
            pos -= p;
            dfs(row|p, (dia1|p)<<1, (dia2|p)>>1, mask, cnt);
        }
    }
    int totalNQueens(int n) {
        int mask = (1<<n)-1, cnt = 0;
        dfs(0, 0, 0, mask, cnt);
        return cnt;
    }
};

int main() {
    Solution s;
    int ret = s.totalNQueens(12);
    cout << ret << endl;
    return 0;
}