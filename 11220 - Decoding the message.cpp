#include <stdio.h>
#include <sstream>
#include <iostream>
using namespace std;
int main() {
    int t, cases = 0;
    char line[1024];
    scanf("%d ", &t);
    while(t--) {
        printf("Case #%d:\n", ++cases);
        while(gets(line)) {
            if(line[0] == '\0') break;
            stringstream sin(line);
            string word;
            int i = 1;
            while(sin >> word) {
                if(word.length() < i)   continue;
                printf("%c", word[i-1]);
                i++;
            }
            puts("");
        }
        if(t)   puts("");
    }
    return 0;
}
