#include <stdio.h>
#include <algorithm>
#include <set>
#include <string.h>
#include <iostream>
using namespace std;
char word[10000][105], s[105];
int wlen[10000];
int main() {
    int n, m, i, j;
    while(scanf("%d", &n) == 1) {
        set<string> S;
        while(getchar() != '\n');
        for(i = 0; i < n; i++) {
            gets(word[i]);
            S.insert(word[i]);
            wlen[i] = strlen(word[i]);
        }
        scanf("%d", &m);
        while(getchar() != '\n');
        while(m--) {
            gets(s);
            if(S.find(s) != S.end()) {
                printf("%s is correct\n", s);
                continue;
            }
            int flag = 0, len = strlen(s);
            for(i = 0; i < n && !flag; i++) {
                if(wlen[i] == len-1) { // one letter is missing
                    int idx1 = 0, idx2 = 0, one = 0;
                    while(idx1 < len && idx2 < len-1) {
                        if(s[idx1] == word[i][idx2])
                            idx1++, idx2++;
                        else {
                            if(!one)
                                idx1++, one = 1;
                            else
                                break;
                        }
                    }
                    if(!one)    idx1++, one = 1;
                    if(idx1 == len && idx2 == len-1 && one == 1) {
                        printf("%s is a misspelling of %s\n", s, word[i]);
                        flag = 1;
                        break;
                    }
                }
                if(wlen[i] == len+1) { // one letter is too much
                    int idx1 = 0, idx2 = 0, one = 0;
                    while(idx1 < len && idx2 < len+1) {
                        if(s[idx1] == word[i][idx2])
                            idx1++, idx2++;
                        else {
                            if(!one)
                                idx2++, one = 1;
                            else
                                break;
                        }
                    }
                    if(!one)    idx2++, one = 1;
                    if(idx1 == len && idx2 == len+1 && one == 1) {
                        printf("%s is a misspelling of %s\n", s, word[i]);
                        flag = 1;
                        break;
                    }
                }
                if(wlen[i] == len) { // one letter is wrong
                    int idx1 = 0, idx2 = 0, one = 0;
                    while(idx1 < len && idx2 < len+1) {
                        if(s[idx1] == word[i][idx2])
                            idx1++, idx2++;
                        else {
                            if(!one)
                                idx1++, idx2++, one = 1;
                            else
                                break;
                        }
                    }
                    if(idx1 == len && idx2 == len && one == 1) {
                        printf("%s is a misspelling of %s\n", s, word[i]);
                        flag = 1;
                        break;
                    }
                }
                if(wlen[i] == len) { // The order of two adjacent letters is wrong
                    int idx1 = 0, idx2 = 0, one = 0, p = 0;
                    while(idx1 < len && idx2 < len+1) {
                        if(s[idx1] == word[i][idx2])
                            idx1++, idx2++;
                        else {
                            if(!one) {
                                swap(s[idx1], s[idx1+1]);
                                p = idx1;
                                one = 1;
                            } else
                                break;
                        }
                    }
                    if(one) swap(s[p], s[p+1]);
                    if(idx1 == len && idx2 == len && one == 1) {
                        printf("%s is a misspelling of %s\n", s, word[i]);
                        flag = 1;
                        break;
                    }
                }
            }
            if(!flag)
                printf("%s is unknown\n", s);
        }
    }
    return 0;
}
