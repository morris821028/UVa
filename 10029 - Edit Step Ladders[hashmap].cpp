#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

int dp[25005];
map<string, int> R[10007];
//adding, deleting, or changing one letter
unsigned int fnv_hash (const void* key, int len) {
    unsigned char* p = (unsigned char *)key;
    unsigned int h = 2166136261UL;
    int i;
    for (i = 0; i < len; i++)
        h = (h*16777619) ^ p[i];
    return h;
}
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
        unsigned int h;
        for(i = 0; i <= len; i++) {//adding
            for(j = 'a'; j <= 'z'; j++) {
                y = x.substr(0, i) + (char)j + x.substr(i);
                h = fnv_hash(y.c_str(), y.length())%10007;
                it = R[h].find(y);
                if(it != R[h].end())
                    mx = max(mx, dp[it->second]);
                if(y.compare(x) > 0)
                    break;
                //cout << y << y.compare(x) << endl;
            }
        }
        for(i = 0; i < len; i++) {//deleting
            y = x.substr(0, i) + x.substr(i+1);
            h = fnv_hash(y.c_str(), y.length())%10007;
            it = R[h].find(y);
            if(it != R[h].end())
                mx = max(mx, dp[it->second]);
            //cout << y << endl;
        }
        y = x;
        for(i = 0; i < len; i++) {//changing
            for(j = 'a'; j <= 'z'; j++) {
                char o = y[i];
                y[i] = j;
                h = fnv_hash(y.c_str(), y.length())%10007;
                it = R[h].find(y);
                if(it != R[h].end())
                    mx = max(mx, dp[it->second]);
                //cout << y << endl;
                y[i] = o;
                if(y.compare(x) > 0)
                    break;
            }
        }
        dp[n] = mx+1;
        ret = max(ret, dp[n]);
        h = fnv_hash(x.c_str(), x.length())%10007;
        R[h][x] = n;
        n++;
    }
    printf("%d\n", ret);
    return 0;
}
