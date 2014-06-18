#include <stdio.h>
#include <iostream>
#include <map>
#include <string.h>
using namespace std;
map<string, int> WORD;
int list[100000];
int mark[100000];
void WORDclear(int i, int L) {
    while(i >= 0 && L >= 0)
        mark[list[i]] = 0, i--, L--;
}
int check(int L, int n, int tot) {
    int i, cnt = tot;
    map<string, int>::iterator it;
    for(i = 0; i < L; i++) {
        if(mark[list[i]] == 0)
            cnt--;
        mark[list[i]]++;
    }
    if(cnt == 0) {
        WORDclear(L-1, L);
        return 0;
    }
    for(i = L; i < n; i++) {
        if(mark[list[i]] == 0)
            cnt--;
        mark[list[i]]++;
        if(mark[list[i-L]] == 1)
            cnt++;
        mark[list[i-L]]--;
        if(cnt == 0) {
            WORDclear(i, L);
            return i-L+1;
        }
    }
    WORDclear(n-1, L);
    return -1;
}
int main() {
    int t, i, j, k, cases = 0;
    char line[1024], buf[1024];
    scanf("%d", &t);
    gets(line);
    while(t--) {
        WORD.clear();
        int n = 0, label = 1, x;
        map<string, int>::iterator it;
        while(gets(line) && strcmp("END", line)) {
            for(i = 0; line[i]; i++) {
                if(line[i] >= 'a' && line[i] <= 'z') {
                    int idx = 0;
                    while(line[i] && line[i] >= 'a' && line[i] <= 'z')
                        buf[idx++] = line[i++];
                    buf[idx] = '\0', i--;
                    it = WORD.find(buf);
                    if(it == WORD.end()) {
                        x = label;
                        WORD[buf] = label++;
                    } else
                        x = it->second;
                    list[n++] = x;
                }
            }
        }
        int L = 0, R = n, m;
        int p, q, tp;
        while(L <= R) { // length of [p, q]
            m = (L+R)/2;
            tp = check(m, n, label-1);
            if(tp >= 0)
                R = m-1, p = tp, q = p+m-1;
            else
                L = m+1;
        }
        printf("Document %d: %d %d\n", ++cases, p+1, q+1);
    }
    return 0;
}
