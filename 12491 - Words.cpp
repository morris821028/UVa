#include <stdio.h>
#include <iostream>
#include <set>
using namespace std;
int N1, N2;
string A[50], B[50];
set<string> sA, sB; // state
int calcPrefix(string a, string b) {
    int la = a.length(), lb = b.length();
    int i;
    for(i = 0; i < la && i < lb; i++)
        if(a[i] != b[i])
            return -1;
    return i;
}
int dfs(string a, string b) {
    if(sA.find(a) != sA.end() || sB.find(b) != sB.end())
        return 0;
    if(a.length() == 0 && b.length() == 0)
        return 1;
    int found = 0, i, prefix;
    if(a.length()) {
        sA.insert(a);
        for(i = 0; i < N2 && !found; i++) {
            prefix = calcPrefix(a, B[i]);
            if(prefix == -1)    continue;
            if(prefix == a.length())
                found |= dfs("", B[i].substr(prefix));
            else
                found |= dfs(a.substr(prefix), "");
        }
    } else {
        sB.insert(b);
        for(i = 0; i < N1 && !found; i++) {
            prefix = calcPrefix(b, A[i]);
            if(prefix == -1)    continue;
            if(prefix == b.length())
                found |= dfs(A[i].substr(prefix), "");
            else
                found |= dfs("", b.substr(prefix));
        }
    }
    return found;
}
int main() {
    int i;
    char s[50];
    while(scanf("%d %d", &N1, &N2) == 2) {
        for(i = 0; i < N1; i++) {
            scanf("%s", s);
            A[i] = s;
        }
        for(i = 0; i < N2; i++) {
            scanf("%s", s);
            B[i] = s;
        }
        sA.clear(), sB.clear();
        int found = 0;
        for(i = 0; i < N1 && !found; i++) {
            found |= dfs(A[i], "");
        }
        puts(found ? "S" : "N");
    }
    return 0;
}
