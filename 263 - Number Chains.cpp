#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
using namespace std;
int cmp1(const void *i, const void *j) {
    return *(char *)i - *(char *)j;
}
int cmp2(const void *i, const void *j) {
    return *(char *)j - *(char *)i;
}
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        char des[20], asc[20];
        sprintf(des, "%d", n);
        sprintf(asc, "%d", n);
        int x, y, chain = 0;
        map<int, int> record;
        printf("Original number was %d\n", n);
        record[n] = 1;
        while(true) {
            chain++;
            qsort(des, strlen(des), sizeof(char), cmp1);
            qsort(asc, strlen(asc), sizeof(char), cmp2);
            sscanf(asc, "%d", &x);
            sscanf(des, "%d", &y);
            n = x - y;
            printf("%d - %d = %d\n", x, y, n);
            if(record[n] == 1)
                break;
            record[n] = 1;
            sprintf(des, "%d", n);
            sprintf(asc, "%d", n);
        }
        printf("Chain length %d\n\n", chain);
    }
    return 0;
}
