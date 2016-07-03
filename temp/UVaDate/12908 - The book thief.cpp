#include <stdio.h> 
#include <algorithm>
using namespace std;

const int MAXN = 131072;
long long pages[MAXN];
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
inline long long ReadInt(long long *x) {
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
	for (long long i = 0; i < MAXN; i++)
		pages[i] = (1 + i) * i / 2;
	long long x;
	while (ReadInt(&x) && x) {
		int pos = (int) (upper_bound(pages, pages+MAXN, x) - pages);
		printf("%lld %d\n", pages[pos] - x, pos);
	}
	return 0;
}
