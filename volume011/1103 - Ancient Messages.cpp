#include <iostream>  
#include <cstdio>  
#include <cstdlib>  
#include <cctype>  
#include <cstring>  
#include <string>  
#include <sstream>  
#include <vector>  
#include <set>  
#include <map>  
#include <algorithm>  
#include <stack>  
#include <queue>  
#include <bitset>   
#include <cassert>   
  
using namespace std;  
  
const int maxh = 205;  
const int maxw = 205;  
  
char bin[256][5];  
  
int H, W, pic[maxh][maxw], color[maxh][maxw];  
char line[maxw];  
  
// 解码成一个01矩阵  
void decode(char ch, int row, int col)  
{  
    for (int i = 0; i < 4; i++) {  
        pic[row][col + i] = bin[ch][i] - '0';  
    }  
}  
  
const int dr[] = { -1, 1, 0, 0 };  
const int dc[] = { 0, 0, -1, 1 };  
  
// DFS遍历，把连通块标记为C  
void dfs(int row, int col, int c)  
{  
    color[row][col] = c;  
    for (int i = 0; i < 4; i++) { // 这道题只需要考虑上下左右  
        int row2 = row + dr[i];  
        int col2 = col + dc[i];  
        if (row2 >= 0 &&  
            row2 < H &&  
            col2 >= 0 &&  
            col2 < W &&  
            pic[row2][col2] == pic[row][col] &&  
            color[row2][col2] == 0) {  
            dfs(row2, col2, c);  
        }  
    }  
}  
  
// 集合数组，记录黑色连通块周围相连的非背景的白块，也就是白洞  
vector<set<int> > neighbors;  
  
void checkNeighbors(int row, int col)  
{  
    for (int i = 0; i < 4; i++) {  
        int row2 = row + dr[i];  
        int col2 = col + dc[i];  
        if (row2 >= 0 &&  
            row2 < H &&  
            col2 >= 0 &&  
            col2 < W &&  
            pic[row2][col2] == 0 &&  
            color[row2][col2] != 1) {  
            neighbors[color[row][col]].insert(color[row2][col2]);  
        }  
    }  
}  
  
const char* code = "WAKJSD";  
  
char recognize(int c)  
{  
    int cnt = neighbors[c].size();  
    return code[cnt];  
}  
  
void print()  
{  
    for (int i = 0; i < H; i++) {  
        for (int j = 0; j < W; j++) {  
            printf("%d", pic[i][j]);  
        }  
        printf("\n");  
    }  
}  
  
int main()  
{  
    strcpy(bin['0'], "0000");  
    strcpy(bin['1'], "0001");  
    strcpy(bin['2'], "0010");  
    strcpy(bin['3'], "0011");  
    strcpy(bin['4'], "0100");  
    strcpy(bin['5'], "0101");  
    strcpy(bin['6'], "0110");  
    strcpy(bin['7'], "0111");  
    strcpy(bin['8'], "1000");  
    strcpy(bin['9'], "1001");  
    strcpy(bin['a'], "1010");  
    strcpy(bin['b'], "1011");  
    strcpy(bin['c'], "1100");  
    strcpy(bin['d'], "1101");  
    strcpy(bin['e'], "1110");  
    strcpy(bin['f'], "1111");  
  
    int kase = 0;  
    while (scanf("%d%d", &H, &W) == 2 && H) {  
        memset(pic, 0, sizeof(pic));  
        for (int i = 0; i < H; i++) {  
            scanf("%s", line);  
            for (int j = 0; j < W; j++) {  
                decode(line[j], i + 1, j * 4 + 1);  
            }  
        }  
  
        H += 2;  
        W = W * 4 + 2;  
  
        int cnt = 0;  
        vector<int> cc; // 黑色连通块的标号存放在cc里面  
        memset(color, 0, sizeof(color));  
        for (int i = 0; i < H; i++) {  
            for (int j = 0; j < W; j++) {  
                if (!color[i][j]) {  
                    dfs(i, j, ++cnt);  
                    if (pic[i][j] == 1) {  
                        cc.push_back(cnt);  
                    }  
                }  
            }  
        }  
        neighbors.clear();  
        neighbors.resize(cnt + 1);  
        for (int i = 0; i < H; i++) {  
            for (int j = 0; j < W; j++) {  
                if (pic[i][j] == 1) {  
                    checkNeighbors(i, j);  
                }  
            }  
        }  
  
        vector<char> ans;  
        for (int i = 0; i < cc.size(); i++) {  
            ans.push_back(recognize(cc[i]));  
        }  
        sort(ans.begin(), ans.end());  
  
        printf("Case %d: ", ++kase);  
        for (int i = 0; i < ans.size(); i++) {  
            printf("%c", ans[i]);  
        }  
        printf("\n");  
    }  
  
    return 0;  
}
