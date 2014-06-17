#include <stdio.h>

int main() {
    int n, i, j, k;
    char S[20][100], E[20][100];
    char line[1024], buf[1024];
    while(gets(line)) {
        sscanf(line, "%d", &n);
        if(n == 0)  break;
        for(i = 0; i < n; i++) {
            gets(S[i]);
            gets(E[i]);
        }
        gets(line);
        for(i = 0; i < n; i++) {
            while(true) {
                int find = -1;
                for(j = 0; line[j]; j++) {
                    for(k = 0; S[i][k]; k++) {
                        if(line[j+k] != S[i][k])
                            break;
                    }
                    if(S[i][k] == '\0') {
                        find = j;
                        break;
                    }
                }
                if(find < 0)    break;
                int idx = 0;
                for(j = 0; j < find; j++)
                    buf[idx++] = line[j];
                for(j = 0; E[i][j]; j++)
                    buf[idx++] = E[i][j];
                for(j = find+k; line[j]; j++)
                    buf[idx++] = line[j];
                buf[idx] = '\0';
                for(j = 0; buf[j]; j++)
                    line[j] = buf[j];
                line[j] = '\0';
            }
        }
        puts(line);
    }
    return 0;
}
