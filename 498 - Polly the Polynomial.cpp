#include <stdio.h>
int parseLine(char *str, int a[]) {
    int i, neg = 1, g = 0, tmp = 0, idx = 0;
    for(i = 0; str[i]; i++) {
        if(str[i] >= '0' && str[i] <= '9')
            tmp = tmp*10 + str[i]-'0', g = 1;
        else {
            if(str[i] == '-') {
                neg = -1;
            } else if(str[i] == '+') {
                neg = 1;
            } else if(g) {
                a[idx++] = tmp*neg;
                g = 0, tmp = 0, neg = 1;
            }
        }
    }
    if(g)
        a[idx++] = tmp*neg;
    return idx;
}
int pow(int x, int y) {
    if(y == 0)
        return 1;
    if(y&1)
        return pow(x*x, y>>1)*x;
    else
        return pow(x*x, y>>1);
}
int main() {
    char line[500];
    int c[500], x[500];
    while(gets(line)) {
        int ct, xt;
        ct = parseLine(line, c);
        gets(line);
        xt = parseLine(line, x);
        int sum, i, j;
        for(i = 0; i < xt; i++) {
            sum = 0;
            for(j = 0; j < ct; j++)
                sum += pow(x[i], ct-j-1)*c[j];
            if(i)
                putchar(' ');
            printf("%d", sum);
        }
        puts("");
    }
    return 0;
}
