#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<string, char> R;
    R["123457"] = 'A', R["1234567"] = 'B';
    R["456"] = 'C', R["1580"] = 'D';
    R["12456"] = 'E', R["1249"] = 'F';
    R["12569"] = 'G', R["13457"] = 'H';
    R["37"] = 'I', R["3567"] = 'J';
    R["13459"] = 'K', R["156"] = 'L';
    R["12357"] = 'M', R["3579"] = 'N';
    R["123567"] = 'O', R["1458"] = 'P';
    R["12347"] = 'Q', R["123459"] = 'R';
    R["12467"] = 'S', R["278"] = 'T';
    R["13567"] = 'U', R["1379"] = 'V';
    R["135790"] = 'W', R["90"] = 'X';
    R["1347"] = 'Y', R["23456"] = 'Z';
    char s[1024];
    while(gets(s)) {
        int i, j;
        for(i = 0; s[i]; i++) {
            if(s[i] < '0' || s[i] > '9')
                putchar(s[i]);
            else {
                j = i;
                int flag = 0;
                while(s[i+1] <= '9') {
                    i++;
                    int tmp = s[i+1];
                    s[i+1] = 0;
                    if(R.find(s+j) != R.end()) {
                        putchar(R[s+j]);
                        flag = 1;
                        s[i+1] = tmp;
                        break;
                    }
                    s[i+1] = tmp;
                }
                if(!flag)   putchar(' '), i = j;
            }
        }
        puts("");
    }
    return 0;
}
