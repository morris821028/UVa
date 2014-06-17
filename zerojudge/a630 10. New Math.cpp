#include <stdio.h>
void n2ch(long long v, int b) {
    if(!v)  return;
    n2ch(v/b, b);
    if(v%b >= 10)
        putchar(v%b+'a'-10);
    else
        putchar(v%b+'0');
}
int main() {
    char s[1024];
    while(gets(s)) {
        int i, j, k;
        long long b, num, op = '+';
        long long buf[150], idx = 0, plus = 1;
        for(i = 0; s[i] != '='; i++) {
            j = i;
            while(s[j] != '^')  j++;
            k = j+1;
            num = b = 0;
            while(s[k] != '+' && s[k] != '-' && s[k] != '*' && s[k] != '=')
                b = b*10 + s[k++]-'0';
            while(s[i] != '^' && s[i] != '=') {
                num = num*b + (s[i] >= 'a' ? (s[i]-'a'+10) : (s[i]-'0'));
                i++;
            }
            if(op == '+')
                buf[idx++] = num;
            else if(op == '-')
                buf[idx++] = -num;
            else
                buf[idx-1] *= num;
            op = s[k];
            if(op == '=')   break;
            i = k;
        }
        b = 0;
        for(i = k+2; s[i]; i++)
            b = b*10 + s[i]-'0';
        long long sum = 0;
        for(i = 0; i < idx; i++)
            sum += buf[i];
        if(sum < 0) putchar('-'), sum *= -1;
        if(sum == 0)    putchar('0');
        n2ch(sum, b);
        printf("^%d\n", b);
    }
    return 0;
}
