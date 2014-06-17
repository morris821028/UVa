#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;
int flag;
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    if(c == '\n')   flag = 1;
    return 1;
}
int main() {
    int k, a;
    string s;
    while(ReadInt(&k)) {
        int pre, x;
        flag = 0;
        ReadInt(&pre);
        printf("q(x):");
        while(!flag) {
            printf(" %d", pre);
            flag = 0;
            ReadInt(&x);
            pre = pre*k+x;
        }
        puts("");
        printf("r = %d\n\n", pre);
    }
    return 0;
}
/*
3
1 -7 15 -8
3
1 -7 15 -9
*/
