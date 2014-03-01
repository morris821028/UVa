#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
#include <sstream>
using namespace std;
int main() {
    char s[1024], d[1024];
    map<string, int> R;
    while(gets(s)) {
        if(!strcmp(s, "#"))
            break;
        R[s] = 0;
    }
    gets(s);
    int i, j, k, len = strlen(s);
    string res;
    int mxcnt = -1;
    for(i = 1; i < 27; i++) {
        for(j = 0; j < len; j++) {
            if(s[j] == ' ') k = 0;
            else            k = s[j]-'A'+1;
            k = (k-i+27)%27;
            if(k == 0)  d[j] = ' ';
            else        d[j] = k+'A'-1;
        }
        d[len] = '\0';
        stringstream sin(d);
        string token;
        int cnt = 0;
        while(sin >> token) {
            map<string, int>::iterator it = R.find(token);
            if(it != R.end())
                cnt++;
        }
        if(cnt > mxcnt)
            res = d, mxcnt = cnt;
    }
    stringstream sin(res);
    string token;
    int col = 0;
    int first = 0;
    while(sin >> token) {
        if(col + token.length() >= 60)
            cout << endl, col = 0, first = 0;
        if(first)   putchar(' ');
        first = 1;
        col += first + token.length();
        cout << token;
    }
    cout << endl;
    return 0;
}
