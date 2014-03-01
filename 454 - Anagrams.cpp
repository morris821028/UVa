#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <iostream>
using namespace std;
int main() {
    int t;
    scanf("%d ", &t);
    while(t--) {
        string line[101];
        int idx = 0, word[101][128] = {};
        int i, j;
        while(getline(cin, line[idx])) {
            if(line[idx] == "")
                break;
            idx++;
        }
        sort(line, line+idx);
        for(j = 0; j < idx; j++) {
            for(i = 0; line[j][i]; i++) {
                if(isalpha(line[j][i])) {
                    word[j][line[j][i]]++;
                }
            }
        }
        for(i = 0; i < idx; i++) {
            for(j = i+1; j < idx; j++) {
                if(!memcmp(word[i], word[j], sizeof(word[i]))) {
                    printf("%s = %s\n", line[i].c_str(), line[j].c_str());
                }
            }
        }
        if(t)
            puts("");
    }
    return 0;
}
