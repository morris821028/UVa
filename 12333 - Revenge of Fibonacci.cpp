#include <stdio.h>
#include <string.h>
const int base = 100000000;
int F[3][100000];
char buf[100];
struct TrieNd {
    int link[10], res;
} ND[4000000];
int NDsize = 0;
void insTrie(char *s, int val) {
    static int i, idx;
    for(i = 0, idx = 0; s[i] && i < 40; i++) {
        if(ND[idx].link[s[i]-'0'] == 0) {
            NDsize++;
            memset(&ND[NDsize], 0, sizeof(TrieNd));
            ND[idx].link[s[i]-'0'] = NDsize;
            ND[NDsize].res = val;
        }
        idx = ND[idx].link[s[i]-'0'];
    }
}
char* funcH(int n, int len) { // head 40 digits
    char *p = buf;
    for(int i = 0; i < 6 && len >= 0; i++, len--) {
        *p++ = F[n][len]/10000000%10+'0';
        *p++ = F[n][len]/1000000%10+'0';
        *p++ = F[n][len]/100000%10+'0';
        *p++ = F[n][len]/10000%10+'0';
        *p++ = F[n][len]/1000%10+'0';
        *p++ = F[n][len]/100%10+'0';
        *p++ = F[n][len]/10%10+'0';
        *p++ = F[n][len]%10+'0';
    }
    *p = '\0';
    p = buf;
    while(*p == '0')    p++;
    return p;
}
void funcF() {
    F[0][0] = 1;
    F[1][0] = 1;
    insTrie(funcH(0, 0), 0);
    int fa = 0, fb = 1, fc = 2;
    int len = 0, i, j;
    for(i = 2; i < 100000; i++) {
        for(j = 0; j <= len; j++)
            F[fc][j] = F[fa][j] + F[fb][j];
        for(j = 0; j <= len; j++) {
            if(F[fc][j] >= base) {
                F[fc][j+1] += F[fc][j]/base;
                F[fc][j] %= base;
            }
        }
        if(F[fc][len+1])    len++;
        insTrie(funcH(fc, len), i);
        fa++, fb++, fc++;
        if(fa == 3) fa = 0;
        if(fb == 3) fb = 0;
        if(fc == 3) fc = 0;
    }
}
int main() {
    memset(&ND[0], 0, sizeof(TrieNd));
    funcF();
    int t, cases = 0;
    char cmd[50];
    int i, idx;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", cmd);
        for(i = 0, idx = 0; cmd[i]; i++) {
            if(!ND[idx].link[cmd[i]-'0'])
                break;
            idx = ND[idx].link[cmd[i]-'0'];
        }
        int res = -1;
        if(cmd[i] == '\0')
            res = ND[idx].res;
        printf("Case #%d: %d\n", ++cases, res);
    }
    return 0;
}
