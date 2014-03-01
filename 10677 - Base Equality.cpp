#include <stdio.h>

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int B1, B2, r1, r2, i;
        scanf("%d %d %d %d", &B1, &B2, &r1, &r2);
        for(i = r2-1; i > r1; i--) {
            int ch[20], j = i, idx = 0;
            while(j) {
                ch[idx] = j%B1;
                j /= B1;
                idx++;
            }
            int base = 1, sum = 0;
            for(j = 0; j < idx; j++)
                sum += ch[j]*base, base *= B2;
            if(sum%i == 0) {
                printf("%d\n", i);
                break;
            }
        }
        if(i == r1)
            puts("Non-existent.");
    }
    return 0;
}
