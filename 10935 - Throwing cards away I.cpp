#include <stdio.h>
#include <queue>
using namespace std;
int main() {
    int n, i, tn;
    while(scanf("%d", &n) == 1 && n) {
        queue<int> q;
        for(i = 1; i <= n; i++) {
            q.push(i);
        }
        int flag = 0, ansflag = 0;
        printf("Discarded cards:");
        while(!q.empty()) {
            tn = q.front();
            q.pop();
            if(q.size() == 0)
                break;
            if(flag == 0) {
                if(ansflag)
                    printf(",");
                ansflag = 1;
                printf(" %d", tn);
            } else {
                q.push(tn);
            }
            flag ^= 1;
        }
        printf("\nRemaining card: %d\n", tn);
    }
    return 0;
}
