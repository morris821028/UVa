#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

int dp[25005];
map<string, int> R[50];
//adding, deleting, or changing one letter
int main() {
    char word[16];
    int n = 0;
    int i, j, ret = 0;
    while(gets(word)) {
        int len = strlen(word);
        int mx = 0;
        string x = word;
        string y;
        map<string, int>::iterator it;
        for(i = 0; i <= len; i++) {//adding
            for(j = 'a'; j <= 'z'; j++) {
                y = x.substr(0, i) + (char)j + x.substr(i);
                it = R[y.length()].find(y);
                if(it != R[y.length()].end())
                    mx = max(mx, dp[it->second]);
                if(y.compare(x) > 0)
                    break;
                //cout << y << y.compare(x) << endl;
            }
        }
        for(i = 0; i < len; i++) {//deleting
            y = x.substr(0, i) + x.substr(i+1);
            it = R[y.length()].find(y);
            if(it != R[y.length()].end())
                mx = max(mx, dp[it->second]);
            //cout << y << endl;
        }
        y = x;
        for(i = 0; i < len; i++) {//changing
            for(j = 'a'; j <= 'z'; j++) {
                char o = y[i];
                y[i] = j;
                it = R[y.length()].find(y);
                if(it != R[y.length()].end())
                    mx = max(mx, dp[it->second]);
                //cout << y << endl;
                y[i] = o;
                if(y.compare(x) > 0)
                    break;
            }
        }
        dp[n] = mx+1;
        ret = max(ret, dp[n]);
        R[x.length()][x] = n;
        n++;
    }
    printf("%d\n", ret);
    return 0;
}
