#include <stdio.h>

int main() {
    char s[105];
    while(gets(s)) {
        int row[6] = {};
        int i, j, k, p;
        for(i = 0; s[i]; i++) {
            p = s[i]-'0';
            for(j = 0; j <= 6-p; j++) {
                if(row[j] != 20) {
                    for(k = 1; k < p; k++)
                        if(row[j+k] != row[j])
                            break;
                    if(k == p) {
                        for(k = 0; k < p; k++)
                            row[j+k]++;
                        j = 10; //accept
                        break;
                    }
                }
            }
            if(j == 10)
                continue;
            for(j = 0; j < 6; j++) {
                if(row[j]+p <= 20) {
                    row[j] += p;
                    break;
                }
            }
            if(j == 6) //not accept
                break; // full
        }
        int sum = 0;
        for(j = 0; j < 6; j++)
            sum += row[j];
        printf("%d %d\n", i, 120-sum);
    }
    return 0;
}
