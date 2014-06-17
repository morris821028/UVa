#include <stdio.h>
#include <string.h>
#include <math.h>
int main() {
    int t, cases = 0;
    int map[100][100];
    scanf("%d", &t);
    getchar();
    while(t--) {
        char line[10001];
        gets(line);
        int i, j;
        for(i = 0, j = 0; line[i]; i++) {
            if(line[i] >= 'a' && line[i] <= 'z')
                line[j++] = line[i];
        }
        line[j] = '\0';
        int len = strlen(line);
        int K = sqrt(len);
        printf("Case #%d:\n", ++cases);
        if(K*K != len) {
            puts("No magic :(");
            continue;
        }
        int flag = 0, idx = 0;
        for(j = 0; j < K; j++) {
            for(i = 0; i < len; i += K) {
                if(line[idx] != line[i+j])
                    flag = 1;
                idx++;
            }
        }
        idx = 0;
        for(i = len-1; i >= 0; i -= K) {
            for(j = 0; j < K; j++) {
                if(line[idx] != line[i-j])
                    flag = 1;
                idx++;
            }
        }
        idx = 0;
        for(j = 0; j < K; j++) {
            for(i = len-1; i >= 0; i -= K) {
                if(line[idx] != line[i-j])
                    flag = 1;
                idx++;
            }
        }
        if(flag)
            puts("No magic :(");
        else
            printf("%d\n", K);
    }
    return 0;
}
