#include <bits/stdc++.h> 

namespace mLocalStream {
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
	class Print {
	public:
		static const int N = 1048576;
	    char buf[N], *p, *end;
		Print() {
			p = buf, end = buf + N - 1;
		}
		void printInt(int x, char padding) {
			static char stk[16];
			int idx = 0;
			stk[idx++] = padding;
			if (!x)	
				stk[idx++] = '0';
			while (x)
				stk[idx++] = x%10 + '0', x /= 10;
			while (idx) {
				if (p == end) {
					*p = '\0';
					printf("%s", buf), p = buf;
				}
				*p = stk[--idx], p++;
			}
		}
		static inline void online_printInt(int x) {
			static char ch[16];
			static int idx;
			idx = 0;
			if (x == 0)	ch[++idx] = 0;
		    while (x > 0) ch[++idx] = x % 10, x /= 10;
		    while (idx) 
		        putchar(ch[idx--]+48);
		}
		~Print() {
			*p = '\0';
			printf("%s", buf);
		}
	} bprint;
}
int main() {
	int x0, p, n;
	while (scanf("%d %d %d", &x0, &p, &n) == 3) {
		for (int i = 0; i < n; i++) {
			mLocalStream::bprint.printInt(x0, i == n-1 ? '\n' : ' ');
//			mLocalStream::Print::online_printInt(x0);
//			putchar(i == n-1 ? '\n' : ' ');
			x0 = ((long long) x0 * x0)%p;
		}
	}
	return 0;
}
