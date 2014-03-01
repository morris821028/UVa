#include <cstdio>
#include <algorithm>

using namespace std;

int n, k[50000];
bool a[50000];

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
    while((c = readchar()) < '-');
    bool neg = (c == '-');
    int x = neg?0:(c - '0');
    while((c = readchar()) >= '0') {
        x = (x << 3) + (x << 1) + c - '0';
    }
    return neg?-x:x;
}

int main() {
    while((n = readint())) {
        int m1 = 1000000001, m2 = -1000000001;
        for(int i = 0; i < n; i++) {
            int x = readint();
            k[i] = x;
            a[i] = false;
            if(x < m1) m1 = x;
            if(x > m2) m2 = x;
        }
        bool b = true;
        if(n >= 3) {
            int d = m2 - m1;
            if(d % (n - 1)) {
                b = false;
                break;
            }
            d /= n - 1;
            if(d) {
                for(int i = 0; i < n; i++) {
                    const int d2 = k[i] - m1, q = d2 / d, r = d2 % d;
                    if(r or q >= n or a[q]) {
                        b = false;
                        break;
                    }
                    a[q] = true;
                }
            }
        }
        puts(b?"Yes":"No");
    }
}
