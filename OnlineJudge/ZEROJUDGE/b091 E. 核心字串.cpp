#include <stdio.h>
#include <queue>
using namespace std;
char s[1000005];
int main() {
    int len;
    while(scanf("%d", &len) == 1 && len) {
        scanf("%s", s+1);
        int address[128] = {}, i, j;
        int tot = 0, ans = 0xffffff;
        queue<int> q;
        for(i = 1; i <= len; i++) {
            q.push(i);
            if(address[s[i]] == 0)
                tot++;
            address[s[i]] = i;
            while(q.front() != address[s[q.front()]])
                q.pop();
            if(tot == 26 && q.size() < ans) {
                ans = q.size();
                j = q.front();
            }
        }
        if(ans != 0xffffff) {
            s[j+ans] = '\0';
            puts(s+j);
        } else
            puts("not found");
    }
    return 0;
}
