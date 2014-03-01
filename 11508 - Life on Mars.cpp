#include <stdio.h>
#include <queue>
#include <iostream>
#include <sstream>
#include <string.h>
using namespace std;

int main() {
    string line;
    while(getline(cin, line)) {
        stringstream sin(line);
        int n = 0, S[10005];
        while(sin >> S[n])  n++;
        if(n == 1 && S[0] == 0)
            break;
        int St[10005], i;
        memset(St, -1, sizeof(St));
        queue<int> Q;
        int err = 0;
        for(i = 0; i < n && !err; i++) {
            if(S[i] >= n)   err = 1;
            else {
                if(St[S[i]] == -1)
                    St[S[i]] = S[i];
                else
                    Q.push(S[i]);
            }
        }
        if(err) {
            puts("Message hacked by the Martians!!!");
            continue;
        }
        for(i = 0; i < n; i++) {
            if(St[i] == -1) {
                St[i] = Q.front();
                Q.pop();
            }
        }
        for(i = 0; i < n; i++) {
            if(i)   putchar(' ');
            printf("%d", St[i]);
        }
        puts("");
    }
    return 0;
}
