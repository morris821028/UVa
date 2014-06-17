#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
using namespace std;
map<string, int> R;
int dfs(string &s) {
    if(s == "")
        return 1;
    map<string, int>::iterator it = R.find(s);
    if(it != R.end())
        return it->second;
    string sub;
    int i, j;
    int &ret = R[s];
    for(i = 0; i < s.length(); i++) {
        for(j = i; j < s.length();j++)
            if(s[i] != s[j])
                break;
        if(j >= i+2) {
            sub = s.substr(0, i) + s.substr(j);
            ret |= dfs(sub);
            if(ret)
                return ret;
            i = j-1;
            //cout << s.substr(0,i) << " * " <<s.substr(j)<< endl;
        }
    }
    return ret;
}
int main() {
    /*freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout);*/
    int testcase;
    string s;
    scanf("%d", &testcase);
    while(testcase--) {
        cin >> s;
        printf("%d\n", dfs(s));
    }
    return 0;
}
/*
50
babbabbbab
abbabbba
Output
1
*/
