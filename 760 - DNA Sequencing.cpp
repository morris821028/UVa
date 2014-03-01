#include <stdio.h>
#include <string.h>
struct TrieNd{
    int LK[26];
    int ac;
} ND[100000];
int TrieSize = 0;
void insTrie(char s[]) {
    static int i, idx, v;
    for(i = 0, idx = 0; s[i]; i++) {
        v = s[i]-'a';
        if(!ND[idx].LK[v]) {
            TrieSize++;
            memset(&ND[TrieSize], 0, sizeof(ND[0]));
            ND[idx].LK[v] = TrieSize;
        }
        idx = ND[idx].LK[v];
    }
}
void matchTrie(char s[]) {
    static int i, idx, v;
    for(i = 0, idx = 0; s[i]; i++) {
        v = s[i]-'a';
        ND[idx].ac = 1;
        if(ND[idx].LK[v])
            idx = ND[idx].LK[v];
        else
            break;
    }
    ND[idx].ac = 1;
}
int mxlen = -1;
void dfs(int nd, int dep) {
    int i;
    for(i = 0; i < 26; i++) {
        if(ND[nd].LK[i] && ND[ND[nd].LK[i]].ac) {
            if(dep+1 > mxlen)
                mxlen = dep+1;
            dfs(ND[nd].LK[i], dep+1);
        }
    }
}
char path[512];
void dfs2(int nd, int dep) {
    int i;
    for(i = 0; i < 26; i++) {
        if(ND[nd].LK[i] && ND[ND[nd].LK[i]].ac) {
            path[dep] = i+'a';
            if(dep+1 == mxlen) {
                path[dep+1] = '\0';
                puts(path);
            }
            dfs2(ND[nd].LK[i], dep+1);
        }
    }
}
int main() {
    char s1[512], s2[512];
    int i, first = 0;
    while(gets(s1)) {
        gets(s2);
        if(first)   puts("");
        first = 1;
        memset(&ND[0], 0, sizeof(ND[0]));
        TrieSize = 0;
        for(i = 0; s1[i]; i++)
            insTrie(s1+i);
        for(i = 0; s2[i]; i++)
            matchTrie(s2+i);
        mxlen = -1;
        dfs(0, 0);
        if(mxlen > 0)
            dfs2(0, 0);
        else
            puts("No common sequence.");
        gets(s1);
    }
    return 0;
}
