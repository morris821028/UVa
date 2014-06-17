#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;
int main() {
    string s, word, tmp;
    getline(cin, s);
    int i, j, k;
    while(getline(cin, s)) {
        getline(cin, word);
        int len = word.length();
        for(i = 0; i < 26; i++) {
            stringstream sin(s);
            bool flag = false;
            while(sin >> tmp) {
                if(tmp.length() == len) {
                    for(j = 0; j < len; j++) {
                        if((word[j]-'a'+i)%26 != tmp[j]-'a')
                            break;
                    }
                    if(j == len)    flag = true;
                }
            }
            if(flag)    putchar(i+'a');
        }
        puts("");
    }
    return 0;
}
