#include <stdio.h>

int main() {
    int n, test = 0;
    while(scanf("%d", &n) == 1 && n) {
        printf("Output for data set %d, %d bytes:\n", ++test, n);
        int sum = 0, cnt = 0;
        int total = 0, x;
        while(scanf("%d", &x) == 1) {
            sum += x;
            n -= x;
            cnt++;
            if(cnt == 5) {
                printf("   Time remaining: ");
                if(sum == 0)
                    puts("stalled");
                else {
                    int tmp = n*5;
                    printf("%d seconds\n", tmp/sum + (tmp%sum != 0));
                }
                sum = 0;
                cnt = 0;
            }
            total++;
            if(n == 0)
                break;
        }
        printf("Total time: %d seconds\n\n", total);
    }
    return 0;
}
