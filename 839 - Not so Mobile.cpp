#include <stdio.h>
int flag, t;
int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int scan() {
    int wl, dl, wr, dr;
    ReadInt(&wl), ReadInt(&dl), ReadInt(&wr), ReadInt(&dr);
    if(!wl)
        wl = scan();
    if(!wr)
        wr = scan();
    if(wl*dl != wr*dr)  flag = 1;
    return wl + wr;
}
int main() {
    scanf("%d", &t);
    while(t--) {
        flag = 0, scan();
        puts(flag ? "NO" : "YES");
        if(t)
            puts("");
    }
    return 0;
}
