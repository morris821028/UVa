#include <stdio.h>
#include <string.h>
char in[5000];
int main() {
    int i, j, k;
    while(scanf("%s", in) == 1) {
        if(!strcmp(in, "0") || !strcmp(in, "1")) {
            puts("Not an Automorphic number.");
            continue;
        }
        int x[3005] = {}, y[3005] = {};
        int len = strlen(in);
        for(i = 0, j = len-1; i < len; i++, j--)
            x[j] = in[i]-'0';
        int top = len-1;
        while(top >= 0 && x[top] == 0)
            top--;
        if(top < 0 || (top == 0 && x[top] == 1)) {
            puts("Not an Automorphic number.");
            continue;
        }
        int error = 0;
        for(i = 0; i < len && !error; i++) {
            if(x[i])
                for(j = 0; i+j < len; j++)
                    y[i+j] += x[i]*x[j];
            y[i+1] += y[i]/10;
            y[i] %= 10;
            if(y[i] != x[i])
                error = 1;
        }
        if(error)
            puts("Not an Automorphic number.");
        else
            printf("Automorphic number of %d-digit.\n", len);
    }
    return 0;
}
