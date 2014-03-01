#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
int P[1005], n;
void step1() {
    int i, j, k;
    for(i = 1; i <= n; i++)
        P[i] = i;
    for(i = 1; i <= 65536; i++) {
        j = rand()%n+1;
        k = rand()%n+1;
        swap(P[j], P[k]);
    }
}// random init solution for n-queen
int column[1005];
int markRight[2005], markLeft[2005];
int error;
int injure[2005], inSize, chNode, chColumn;
int mnAttack[2005], mnSize;
int mn;
void step2a() {
    int i, x, y, right, left;
    inSize = 0;
    for(i = 1; i <= n; i++) {
        x = i, y = P[i];
        if(x >= y)  right = x-y;
        else        right = y-x+n;
        x = i, y = n-P[i]+1;
        if(x >= y)  left = x-y;
        else        left = y-x+n;
        if(column[P[i]] > 1 || markRight[right] > 1 || markLeft[left] > 1) {
            injure[inSize++] = i;
        }
    }
    if(inSize == 0) {
        printf("%d XXX\n", error);
    }
    chNode = injure[rand()%inSize];
    //printf("injure %d\n", inSize);
    x = chNode, y = P[chNode];
    if(x >= y)  right = x-y;
    else        right = y-x+n;
    x = chNode, y = n-P[chNode]+1;
    if(x >= y)  left = x-y;
    else        left = y-x+n;
    if(column[P[chNode]] == 2)  error--;
    if(markRight[right] == 2)   error--;
    if(markLeft[left] == 2)     error--;
    column[P[chNode]]--, markRight[right]--, markLeft[left]--;
    mn = column[P[chNode]]+markRight[right]+markLeft[left];
}
void step2b() {
    int i, x, y, right, left, tmp;
    mnSize = 0;
    for(i = 1; i <= n; i++) {
        x = chNode, y = i;
        if(x >= y)  right = x-y;
        else        right = y-x+n;
        x = chNode, y = n-i+1;
        if(x >= y)  left = x-y;
        else        left = y-x+n;
        tmp = column[i] + markRight[right] + markLeft[left];
        //printf("i %d : %d %d queen\n", i, tmp, mn);
        if(tmp <= mn)
            mnAttack[mnSize++] = i;
    }
    /*printf("set :");
    for(i = 0; i < mnSize; i++)
        printf(" %d", mnAttack[i]);
    puts("");*/
    if(mnSize == 0) {
        for(i = 1; i <= n; i++) {
            x = chNode, y = i;
            if(x >= y)  right = x-y;
            else        right = y-x+n;
            x = chNode, y = n-i+1;
            if(x >= y)  left = x-y;
            else        left = y-x+n;
            tmp = column[i] + markRight[right] + markLeft[left];
            //printf("i %d : %d %d queen\n", i, tmp, mn);
            if(tmp == mn)
                mnAttack[mnSize++] = i;
        }
    }
    chColumn = mnAttack[rand()%mnSize];
    P[chNode] = chColumn;
    x = chNode, y = P[chNode];
    if(x >= y)  right = x-y;
    else        right = y-x+n;
    x = chNode, y = n-P[chNode]+1;
    if(x >= y)  left = x-y;
    else        left = y-x+n;
    if(column[P[chNode]] == 1)  error++;
    if(markRight[right] == 1)   error++;
    if(markLeft[left] == 1)     error++;
    column[P[chNode]]++, markRight[right]++, markLeft[left]++;
}
int step2() {
    error = 0;
    memset(column, 0, sizeof(column));
    memset(markRight, 0, sizeof(markRight));
    memset(markLeft, 0, sizeof(markLeft));
    int i, x, y, right, left;
    for(i = 1; i <= n; i++) {
        x = i, y = P[i];
        if(x >= y)  right = x-y;
        else        right = y-x+n;
        x = i, y = n-P[i]+1;
        if(x >= y)  left = x-y;
        else        left = y-x+n;
        markRight[right]++;
        markLeft[left]++;
        column[y]++;
    }
    for(i = 0; i < 2*n; i++) {
        if(markRight[i] > 1)
            error++;
        if(markLeft[i] > 1)
            error++;
    }
    int times = 0;
    while(error) {
        times++;
        /*printf("%d", P[1]);
        for(i = 2; i <= n; i++)
            printf(" %d", P[i]);
        puts("");*/
        step2a();
        step2b();
        /*printf("%d", P[1]);
        for(i = 2; i <= n; i++)
            printf(" %d", P[i]);
        puts("");*/
        /*printf("chNode %d column %d\n", chNode, chColumn);
        printf("error %d\n", error);*/
    //    getchar();
        /*if(times > 300) {
            puts("unluck");
            break;
        }*/
    }
    //printf("%d\n", times);
    return 1;
}
int main() {
    srand(514);
    int i;
    puts("char ans[1005][5005] = {{""},{""}");
    while(scanf("%d", &n) == 1) {
        if(n <= 3) {
            puts(",{\"Impossible\"}");
            continue;
        }
        step1();
        step2();
        srand(rand());
        printf(",{\"");
        printf("%d", P[1]);
        for(i = 2; i <= n; i++)
            printf(" %d", P[i]);
        puts("\"}");
    }
    puts("};");
    return 0;
}
