#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char name[105][150];
int time[105], IDX[105];
bool cmp(int a, int b) {
    if(time[a] != time[b])
        return time[a] < time[b];
    return strcasecmp(name[a], name[b]) < 0;
}
int main() {
    int n, i, j;
    int mm, ss, mss;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++) {
            scanf("%s : %d min %d sec %d ms", &name[i], &mm, &ss, &mss);
            time[i] = mss + ss*1000 + mm*60000;
            IDX[i] = i;
        }
        sort(IDX, IDX+n, cmp);
        for(i = 0, j = 1; i < n; i += 2, j++) {
            printf("Row %d\n", j);
            puts(name[IDX[i]]);
            if(i+1 < n)
                puts(name[IDX[i+1]]);
        }
        puts("");
    }
    return 0;
}
