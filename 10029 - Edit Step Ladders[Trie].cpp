#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
struct Node {
    Node *next[26];
    int label;
    Node() {
        label = -1;
        memset(next, 0, sizeof(next));
    }
};
void insertTrie(const char *str, Node *root, int label) {
    static Node *p;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = str[i]-'a';
        if(p->next[idx] == NULL)
            p->next[idx] = new Node();
        p = p->next[idx];
    }
    p->label = label;
}
int findTrie(const char *str, Node *root) {
    static Node *p;
    static int i, idx;
    p = root;
    for(i = 0; str[i]; i++) {
        idx = str[i]-'a';
        p = p->next[idx];
        if(p == NULL)   return -1;
    }
    return p->label;
}
int dp[25005];
//adding, deleting, or changing one letter
int main() {
    char word[16];
    int n = 0;
    Node *root = new Node();
    int i, j, ret = 0;
    while(gets(word)) {
        int len = strlen(word);
        int mx = 0;
        int findret = -1;
        string x = word;
        string y;
        for(i = 0; i <= len; i++) {//adding
            for(j = 'a'; j <= 'z'; j++) {
                y = x.substr(0, i) + (char)j + x.substr(i);
                findret = findTrie(y.c_str(), root);
                if(findret >= 0)
                    mx = max(mx, dp[findret]);
                if(y.compare(x) > 0)
                    break;
                //cout << y << y.compare(x) << endl;
            }
        }
        for(i = 0; i < len; i++) {//deleting
            y = x.substr(0, i) + x.substr(i+1);
                findret = findTrie(y.c_str(), root);
                if(findret >= 0)
                    mx = max(mx, dp[findret]);
            //cout << y << endl;
        }
        y = x;
        for(i = 0; i < len; i++) {//changing
            for(j = 'a'; j <= 'z'; j++) {
                char o = y[i];
                y[i] = j;
                findret = findTrie(y.c_str(), root);
                if(findret >= 0)
                    mx = max(mx, dp[findret]);
                //cout << y << endl;
                y[i] = o;
                if(y.compare(x) > 0)
                    break;
            }
        }
        dp[n] = mx+1;
        ret = max(ret, dp[n]);
        insertTrie(x.c_str(), root, n);
        n++;
    }
    printf("%d\n", ret);
    return 0;
}
