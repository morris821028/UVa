#include <stdio.h>
#include <string.h>
int getNum(char s[]) {
    static const char m[][20] = {
        "pop", "no", "zip", "zotz", "tzec",
        "xul", "yoxkin", "mol", "chen", "yax",
        "zac", "ceh", "mac", "kankin", "muan",
        "pax", "koyab", "cumhu", "uayet"
    };
    int i;
    for(i = 0; ; i++)
        if(!strcmp(m[i], s))
            return i;
}
int main() {
    const char D[][20] = {
        "imix", "ik", "akbal", "kan", "chicchan",
        "cimi", "manik", "lamat", "muluk", "ok",
        "chuen", "eb", "ben", "ix", "mem", "cib",
        "caban", "eznab", "canac", "ahau"
    };
    int t;
    scanf("%d", &t);
    printf("%d\n", t);
    while(t--) {
        int DD, YY;
        char MM[30];
        scanf("%d. %s %d", &DD, MM, &YY);
        int tot;
        tot = YY*365 + getNum(MM)*20 + DD;
        printf("%d %s %d\n", tot%13+1, D[tot%20], tot/260);
    }
    return 0;
}
