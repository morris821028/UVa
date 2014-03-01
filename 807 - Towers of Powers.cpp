#include <stdio.h>
#include <string.h>
#define ULL unsigned long long
char paintmap[100][1000];
int ptr, mxdep;
void transform(ULL n, ULL b, int dep) {
    if(dep > mxdep) mxdep = dep;
    if(n <= b)  {
        sprintf(paintmap[dep]+ptr, "%llu", n);
        while(paintmap[dep][ptr] != '\0')
            ptr++;
        paintmap[dep][ptr] = ' ';
        return;
    }
    ULL buf[70] = {};
    int idx = 0, rear = 0;
    while(n) {
        buf[idx++] = n%b;
        n /= b;
    }
    while(buf[rear] == 0)
        rear++;
    for(; idx >= rear; idx--) {
        if(buf[idx] != 0) {
            if(idx) {
                if(buf[idx] == 1)
                    sprintf(paintmap[dep]+ptr, "%llu", b);
                else
                    sprintf(paintmap[dep]+ptr, "%llu*%llu", buf[idx], b);
            } else {
                sprintf(paintmap[dep]+ptr, "%llu", buf[idx]);
            }
            while(paintmap[dep][ptr] != '\0')
                ptr++;
            paintmap[dep][ptr] = ' ';
            if(idx > 1)
                transform(idx, b, dep+1);
            if(idx != rear) {
                sprintf(paintmap[dep]+ptr, "+");
                while(paintmap[dep][ptr] != '\0')
                    ptr++;
                paintmap[dep][ptr] = ' ';
            }
        }
    }
}
int main() {
    ULL n, b;
    int first = 0;
    char chtmp[100];
    while(scanf("%llu %llu", &n, &b) == 2) {
        if(!n && !b)    break;
        if(first)
            puts("--------------------------------------------------------------------------------");
        first++;
        memset(paintmap, ' ', sizeof(paintmap));
        printf("%llu in complete base %llu:\n", n, b);
        ptr = 0, mxdep = 0;
        transform(n, b, 0);
        char buf[50], space[50];
        int spacelen, eachline;
        int i, j;
        sprintf(buf, "%llu = ", n);
        spacelen = strlen(buf);
        memset(space, ' ', sizeof(space));
        space[spacelen] = '\0';
        eachline = 82 - spacelen;
        for(i = 0; i <= mxdep; i++) {
            j = 999;
            while(j >= 0 && paintmap[i][j] == ' ')
                paintmap[i][j] = '\0', j--;
        }
        int printprocess = 0, time = 0;
        for(; paintmap[0][printprocess]; time++) {
            puts("");
            int pre = -1, next = printprocess;
            while(paintmap[0][next] && next-printprocess+1 < eachline) {
                if(paintmap[0][next] == '+')
                    pre = next;
                next++;
            }
            if(next-printprocess+1 < eachline) {
                pre = 999;
            }
            for(i = 0; i <= mxdep; i++) {
                j = pre;
                chtmp[i] = paintmap[i][pre];
                paintmap[i][pre] = '\0';
                while(j >= printprocess && (paintmap[i][j] == ' ' || paintmap[i][j] == '\0'))
                    paintmap[i][j] = '\0', j--;
            }
            for(i = mxdep; i >= 0; i--, puts("")) {
                if(time == 0 && i == 0)
                    printf("%s", buf);
                else if(paintmap[i][printprocess])
                    printf("%s", space);
                printf("%s", paintmap[i]+printprocess);
            }
            for(i = 0; i <= mxdep; i++)
                paintmap[i][pre] = chtmp[i];
            printprocess = pre;
        }
    }
    return 0;
}
/*
10000000 2
*/
