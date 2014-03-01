#include <stdio.h>
int n, i, j, k;
int alpha[105][2];
char s[105];
void solve() {
    int stack[105], sidx = -1;
    int sum = 0, alidx = 'Z';
    for(i = 0; s[i]; i++) {
        if(s[i] == '(') {
            stack[++sidx] = '(';
        } else if(s[i] == ')'){
            j = sidx;
            while(stack[j] != '(')
                j--;
            for(k = j+1; k < sidx; k++) {
                if(alpha[stack[k]-'A'][1] != alpha[stack[k+1]-'A'][0]) {
                    //printf("%d %d %d %d\n", alpha[stack[k]-'A'][0], alpha[stack[k]-'A'][1], alpha[stack[k+1]-'A'][0], alpha[stack[k+1]-'A'][1]);
                    puts("error");
                    return;
                }
                sum += alpha[stack[k]-'A'][0]*alpha[stack[k]-'A'][1]*alpha[stack[k+1]-'A'][1];
            }
            alidx++;
            alpha[alidx-'A'][0] = alpha[stack[j+1]-'A'][0];
            alpha[alidx-'A'][1] = alpha[stack[sidx]-'A'][1];
            //printf("%d %d %d\n", alpha[alidx][0], alpha[alidx][1], alidx);
            stack[j] = alidx;
            sidx = j;
        } else
            stack[++sidx] = s[i];
    }
    printf("%d\n", sum);
}
int main() {
    int x, y;
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%s %d %d", s, &x, &y);
        alpha[s[0]-'A'][0] = x;
        alpha[s[0]-'A'][1] = y;
    }
    while(scanf("%s", s) == 1) {
        solve();
    }
    return 0;
}
