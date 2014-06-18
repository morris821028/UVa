#include <stdio.h>
char s[100005];
int L[100005], R[100005];
int main() {
    while(gets(s+1)) {
        int i;
        L[0] = R[0] = 0; // head, double linked list
        for(i = 1; s[i]; i++) {
            if(s[i] == '[')
                L[i] = 0, R[i] = R[0];
            else if(s[i] == ']')
                L[i] = L[0], R[i] = 0;
            else
                L[i] = i-1, R[i] = R[i-1];
            L[R[i]] = i, R[L[i]] = i;
        }
        for(i = R[0]; i; i = R[i])
            if(s[i] != '[' && s[i] != ']')
            putchar(s[i]);
        puts("");
    }
    return 0;
}
