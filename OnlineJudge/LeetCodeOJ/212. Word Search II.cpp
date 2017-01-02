#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    struct Node {
        Node *next[26];
        int cnt, label;
        void init() {
            cnt = label = 0;
            memset(next, 0, sizeof(next));
        }
    };
    Node *root, *nodes;
    int size, n, m;
    Node* newNode() {
        Node *p = &nodes[size++];
//        Node *p = new Node();
        p->init();
        return p;
    }
    int toIndex(char c) {
        return c - 'a';
    }
   void addWord(string word) {
        Node *u = root;
        for (int i = 0; i < word.length(); i++) {
            int c = toIndex(word[i]);
            if (u->next[c] == NULL)
                u->next[c] = newNode();
            u->cnt++;
            u = u->next[c];
        }
        u->label |= 1, u->cnt++;
    }
     void removeWord(string word) {
        Node *u = root;
        for (int i = 0; i < word.length(); i++) {
            int c = toIndex(word[i]);
            if (u->next[c] == NULL)
                return ;
            u->cnt--;
            u = u->next[c];
        }
        u->label ^= 1, u->cnt--;
    }
    void dfs(char s[], int idx, int x, int y, Node *u, vector<vector<char>>& board, 
        vector< vector<int> > &used, vector<string> &ret) {
        if (x < 0 || y < 0 || x >= n || y >= m || u == NULL || used[x][y])
            return ;
        int c = toIndex(board[x][y]);
        s[idx] = board[x][y];
        u = u->next[c];
        if (u == NULL || u->cnt == 0)
            return ;
        if (u->label) {
            s[idx+1] = '\0';
            removeWord(s);
            ret.push_back(s);
        }
        used[x][y] = 1;
        dfs(s, idx+1, x+1, y, u, board, used, ret);
        dfs(s, idx+1, x-1, y, u, board, used, ret);
        dfs(s, idx+1, x, y+1, u, board, used, ret);
        dfs(s, idx+1, x, y-1, u, board, used, ret);
        used[x][y] = 0;
    }
    vector<string> findWords(vector< vector<char> >& board, vector<string>& words) {
    	int tot = 1;
    	for (auto s: words)
    		tot += s.length();
    	nodes = (Node *) malloc(sizeof(Node)*tot);
        size = 0;
        root = newNode();
        for (auto s: words)
            addWord(s);
            
        vector<string> ret;
        if (board.size() == 0 || board[0].size() == 0) {
        	free(nodes);
            return ret;
        }
            
        n = board.size(), m = board[0].size();
        vector< vector<int> > used(n, vector<int>(m, 0));
        char s[1024];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dfs(s, 0, i, j, root, board, used, ret);
            }
        }
        free(nodes);
        return ret;
    }
};
Solution t;
int main() {
	int n = 4, m = 4;
	char g[][10] = {"oaan","etae","ihkr","iflv"};
	char w[][10] = {"oath","pea","eat","rain"};
	vector< vector<char> > board;
	for (int i = 0; i < n; i++) {
		board.push_back(vector<char>());
		for (int j = 0; j < m; j++)
			board[i].push_back(g[i][j]);
	}
	vector<string> words;
	for (int i = 0; i < 4; i++)
		words.push_back(w[i]);
	vector<string> ret = t.findWords(board, words);
	for (auto s : ret)
		cout << s << endl;
	return 0;
}

