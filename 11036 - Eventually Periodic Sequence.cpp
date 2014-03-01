#include <stdio.h>
#include <map>
using namespace std;
int main() {
    char s[20], ch;
    int N, n, i, j;
    int p[100][2];
    long long stk[100], a, b;
    while(scanf("%d %d", &N, &n) == 2) {
        if(N == 0 && n == 0)
            break;
        int idx = 0, cnt;
        while(scanf("%s%c", s, &ch) == 2) {
            if(s[0] >= '0' && s[0] <= '9')
                sscanf(s, "%d", &p[idx][0]), p[idx][1] = 1;
            else
                p[idx][0] = s[0], p[idx][1] = 0;
            idx++;
            if(ch == '\n')
                break;
        }
        map<int, int> R[512];
        map<int, int>::iterator it;
        int stkIdx = -1;
        for(cnt = 1; ; cnt++) {
            it = R[n&511].find(n);
            if(it == R[n&511].end()) {
                R[n&511][n] = cnt;
            } else {
                printf("%d\n", cnt-it->second);
                break;
            }
            for(j = 0, stkIdx = -1; j < idx; j++) {
                if(p[j][1] == 1)
                    stk[++stkIdx] = p[j][0];
                else {
                    if(p[j][0] == 'x')
                        stk[++stkIdx] = n;
                    else if(p[j][0] == 'N')
                        stk[++stkIdx] = N;
                    else {
                        b = stk[stkIdx--];
                        a = stk[stkIdx--];
                        if(p[j][0] == '+')
                            stk[++stkIdx] = a+b;
                        else if(p[j][0] == '*')
                            stk[++stkIdx] = a*b;
                        else
                            stk[++stkIdx] = a%b;
                        if(stk[stkIdx] >= N)
                            stk[stkIdx] %= N;
                    }
                }
            }
            n = stk[0];
        }
    }
    return 0;
}
