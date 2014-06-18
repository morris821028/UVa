#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxL (17000000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
using namespace std;
int dp[65][65][65][65];
int appA[65][65], appB[65][65];
int mark[maxL];
char A[105], B[105];
int LA, LB;
int mapped[1008];
int dfs(int la, int ra, int lb, int rb) {
    if(la > ra || lb > rb)  return 0;
    if(GET((la<<18)|(ra<<12)|(lb<<6)|(rb)))
        return dp[la][ra][lb][rb];
    SET((la<<18)|(ra<<12)|(lb<<6)|(rb));
    int &ret = dp[la][ra][lb][rb];
    int sla, sra, slb, srb;
    int com = appA[la][ra]&appB[lb][rb], i;
    ret = 0;
    //for(int i = 'a'; i <= 'z'; i++) {
    while(com) {
        i = mapped[(com&(-com))%1007]+'a';
        com ^= com&(-com);
        sla = la;
        while(sla <= ra && A[sla] != i)     sla++;
        if(sla > ra)    continue;
        sra = ra;
        while(sra >= sla && A[sra] != i)    sra--;
        if(sra < sla)    continue;
        slb = lb;
        while(slb <= rb && B[slb] != i)     slb++;
        if(slb > rb)    continue;
        srb = rb;
        while(srb >= slb && B[srb] != i)    srb--;
        if(srb < slb)    continue;
        if(sla == sra || slb == srb)
            ret = max(ret, 1);
        else
            ret = max(ret, dfs(sla+1, sra-1, slb+1, srb-1)+2);
    }
    return ret;
}
int main() {
    for(int i = 0; i < 26; i++) {
        if(mapped[(1<<i)%1007])
            puts("error");
        mapped[(1<<i)%1007] = i;
    }
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        scanf("%s %s", &A, &B);
        LA = strlen(A), LB = strlen(B);
        memset(mark, 0, sizeof(mark));
        int usedA[128] = {}, usedB[128] = {};
        int i, j;
        for(i = 0; i < LA; i++)
            usedA[A[i]-'a'] = 1;
        for(i = 0; i < LB; i++)
            usedB[B[i]-'a'] = 1;
        for(i = 0, j = 0; i < LA; i++)
            if(usedB[A[i]-'a'])
                A[j++] = A[i];
        A[j] = '\0';
        for(i = 0, j = 0; i < LB; i++)
            if(usedA[B[i]-'a'])
                B[j++] = B[i];
        B[j] = '\0';
        LA = strlen(A);
        LB = strlen(B);
        if(LA == 0 || LB == 0) {
            printf("Case %d: 0\n", ++cases);
            continue;
        }
        for(i = 0; i < LA; i++) {
            appA[i][i] = 1<<(A[i]-'a');
            for(j = i+1; j < LA; j++) {
                appA[i][j] = appA[i][j-1]|(1<<(A[j]-'a'));
            }
        }
        for(i = 0; i < LB; i++) {
            appB[i][i] = 1<<(B[i]-'a');
            for(j = i+1; j < LB; j++) {
                appB[i][j] = appB[i][j-1]|(1<<(B[j]-'a'));
            }
        }
        printf("Case %d: %d\n", ++cases, dfs(0, LA-1, 0, LB-1));
    }
    return 0;
}
/*
100
gabgcccbadacg
gabxxxbacccgbadab
cfcfaafc
efagfc
afbcdfca
bcadfcgyfka
palin
drome
*/
