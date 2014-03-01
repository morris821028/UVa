#include<stdio.h>
#include<stdlib.h>
int Way[100000] = {0, 1}, Ans;
long long Step, P[70000] = {0, 1};    
const int N = 30000000;
static char buf[N];
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int readint() {
    int c;
    while((c = readchar()) < '-') {
		if(c == EOF) return EOF;
	}
    bool neg = (c == '-');
    int x = neg?0:(c - '0');
    while((c = readchar()) >= '0') {
        x = (x << 3) + (x << 1) + c - '0';
    }
    return neg?-x:x;
}
/*char s[10000000];
int st = 0;*/
main() {
    int L, a; 
    for(a = 2; a < 70000; a++)    P[a] = P[a-1] + a; 
    while((L = readint()) != EOF) {
        Ans = 1, Step = 1, L--;
        while(L) {
            Ans++;
            if(P[Step+1] <= L)  Step++;
            else  if(P[Step] > L) Step--;
            Way[Ans] = Step, L -= Step;
        }
        for(a = Ans;a >= 1; a--)
            printf("%d ", Way[a]);
        puts(""); 
    }
    return 0;
}
