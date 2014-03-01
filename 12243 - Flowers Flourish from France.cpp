#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;

int main() {
    char buf[1000];
    while(gets(buf)) {
        if(buf[0] == '*' && buf[1] == '\0')
            break;
        stringstream sin(buf);
        string word;
        sin >> word;
        char last = word[0];
        if(last >= 'a') last = last-'a'+'A';
        while(sin >> word) {
            if(word[0] >= 'a')
                word[0] = word[0]-'a'+'A';
            if(word[0] != last) {
                last = -1;
                break;
            }
        }
        if(last < 0)    puts("N");
        else            puts("Y");
    }
    return 0;
}
