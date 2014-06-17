#include <stdio.h>
int p[100005], q[100005];
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
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, testcase, cases = 0;
    int i, j, k;
    int *a, *b;
    ReadInt(&testcase);
    //scanf("%d", &testcase);
    while(testcase--) {
        ReadInt(&n);
        //scanf("%d", &n);
        a = p, b = q;
        for(i = 0; i < n; i++) {
            ReadInt(a), a++;
            //scanf("%d", p+i);
        }
        for(i = 0; i < n; i++) {
            ReadInt(b), b++;
            //scanf("%d", q+i);
        }
        a = p, b = q;
        int sum = 0;
        for(i = 0; i < n; i++) {
            sum += (*a) - (*b);
            a++, b++;
        }
        printf("Case %d: ", ++cases);
        if(sum < 0) {
            puts("Not possible");
            continue;
        }
        for(i = 0; i < n; i++) {
            j = i, sum = 0, k = 0;
            a = p+j, b = q+j;
            while(sum >= 0) {
                sum += *a - *b;
                j++, k++, a++, b++;
                if(j >= n)  j = 0, a = p, b = q;
                if(k == n)  break;
            }
            if(k == n && sum >= 0) {
                printf("Possible from station %d\n", i+1);
                break;
            }
            if(j < i)   break;
            i = j-1;
        }
    }
    return 0;
}
/*
100
9
1 3 1 4 2 1 2 3 2
2 2 1 3 1 3 1 1 1
5
2 6 7 1 1
3 7 1 1 1
6
1 8 9 6 4 1
9 1 1 2 3 2
7
13 1 2 1 3 1 2
1 2 3 1 14 3 1
6
1 2 3 4 1 4
12 3 2 1 2 1
5
3 4 4 5 6
2 1 1 14 1
*/
