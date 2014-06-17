#include <stdio.h>
char s[1005], *p;
int Slump() {
    if(*p != 'D' && *p != 'E')
        return 0;
    p++;
    if(*p != 'F')
        return 0;
    while(*p == 'F')    p++;
    if(*p == 'G') {
        p++;
        return 1;
    }
    return Slump();
}
int Slimp() {
    if(*p != 'A')
        return 0;
    p++;
    if(*p == 'H') {
        p++;
        return 1;
    }
    if(*p == 'B') {
        p++;
        bool flag = Slimp() && *p == 'C';
        p++;
        return flag;
    }
    bool flag = Slump() && *p == 'C';
    p++;
    return flag;
}
int main() {
    int t;
    scanf("%d", &t);
    puts("SLURPYS OUTPUT");
    while(t--) {
        scanf("%s", s);
        p = s;
        bool flag = Slimp() && Slump() && *p == '\0';
        puts(flag ? "YES" : "NO");
    }
    puts("END OF OUTPUT");
    return 0;
}
