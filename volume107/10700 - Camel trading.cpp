#include <stdio.h>
#include <string.h>
int main() {
    int n;
    char str[100];
    scanf("%d ", &n);
    while(n--) {
        scanf("%s", str);
        long long smax[100], smin[100], tmp = 0;
        int i, idx1 = 0, idx2 = 0, slen = strlen(str);
        char op = '+';
        for(i = 0; i <= slen; i++) {
            if(str[i] >= '0' && str[i] <= '9') {
                tmp = tmp*10 + str[i]-'0';
            } else {
                if(op == '+') {
                    if(idx1 == 0)
                        smax[idx1++] = tmp;
                    else
                        smax[idx1-1] += tmp;
                    smin[idx2++] = tmp;
                } else {
                    if(idx2 == 0)
                        smin[idx2++] = tmp;
                    else
                        smin[idx2-1] *= tmp;
                    smax[idx1++] = tmp;
                }
                op = str[i], tmp = 0;
            }
        }
        long long amax = 1, amin = 0;
        for(i = 0; i < idx1; i++)
            amax *= smax[i];
        for(i = 0; i < idx2; i++)
            amin += smin[i];
        printf("The maximum and minimum are %lld and %lld.\n", amax, amin);
    }
    return 0;
}
