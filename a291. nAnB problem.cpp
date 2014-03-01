#include <stdio.h>

int main() {
    int a, b, c, d, n;
    int a1, b1, c1, d1;
    while(scanf("%d %d %d %d", &a, &b, &c, &d) == 4) {
        scanf("%d", &n);
        getchar();
        while(n--) {
            a1 = getchar() - '0';
            getchar();
            b1 = getchar() - '0';
            getchar();
            c1 = getchar() - '0';
            getchar();
            d1 = getchar() - '0';
            getchar();
            int num[10] = {}, A = 0, B = 0;
            num[a]++, num[b]++, num[c]++, num[d]++;
            if(num[a1]) num[a1]--, B++;
            if(num[b1]) num[b1]--, B++;
            if(num[c1]) num[c1]--, B++;
            if(num[d1]) num[d1]--, B++;
            if(a == a1) A++, B--;
            if(b == b1) A++, B--;
            if(c == c1) A++, B--;
            if(d == d1) A++, B--;
            printf("%dA%dB\n", A, B);
        }
    }
    return 0;
}
