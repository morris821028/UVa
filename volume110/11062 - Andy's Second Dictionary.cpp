#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;

int main() {
    int i, idx = 0;
    map<string, char> record;
    char ch, str[200];
    while(1) {
        ch = getchar();
        if(ch == EOF)   break;
        if(ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if(ch >= 'a' && ch <= 'z') {
            str[idx++] = ch;
        } else if(ch != '-') {
            str[idx++] = '\0';
            if(idx > 1) {
                record[str] = 1;
            }
            idx = 0;
        } else {
            ch = getchar();
            if(ch != '\n') {
                str[idx++] = '-';
                if(ch >= 'A' && ch <= 'Z')
                    ch = ch - 'A' + 'a';
                str[idx++] = ch;
            }
        }
    }
    for(map<string, char>::iterator i = record.begin(); i != record.end(); i++)
        puts(i->first.c_str());
    return 0;
}
