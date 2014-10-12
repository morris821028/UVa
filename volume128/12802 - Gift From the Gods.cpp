#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define maxL (1000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 1000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        }
    }
}
int isPalindromePrime(int n) {
	if (n == 1)	return 1;
	if (GET(n))	return 0;
	char buf[20];
	sprintf(buf, "%d", n);
	int m = strlen(buf);
	for (int i = 0, j = m-1; i < j; i++, j--)
		if (buf[i] != buf[j])
			return 0;
	return 1;
}
int main() {
	sieve();
	int n;
	while (scanf("%d", &n) == 1) {
		printf("%d\n", n<<1);
		if (isPalindromePrime(n))
			break;
	}
	return 0;
}
