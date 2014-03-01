#include <stdio.h>
union S {
    int Integer;
    char Character;
    double Double;
    float Float;
    unsigned long long ULL;
    long long LL;
} V;
int main() {
    V.LL = -1;
    for(int i = 63; i >= 0; i--)
        printf("%d",(V.ULL>>i)&1);
    puts("");
    V.Character = 0;
    for(int i = 63; i >= 0; i--)
        printf("%d",(V.ULL>>i)&1);
    puts("");
    V.Double = 12.234;
    for(int i = 63; i >= 0; i--)
        printf("%d",(V.ULL>>i)&1);
    puts("");
    return 0;
}
