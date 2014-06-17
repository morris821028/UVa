#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define maxL (10000000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
#define RSET(x) (mark[(x)>>5] = 0)
int mark[maxL];
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
	int T; ReadInt(&T);
	while (T--) {
		int v, e; ReadInt(&v), ReadInt(&e);
		vector<int> g[v];
		for (int i = 0, a, b; i < e; ++i) {
		    ReadInt(&a), ReadInt(&b);
			a--, b--;
			if(a > b) {
                g[b].push_back(a);
                SET(a*3001+b);
			} else {
                g[a].push_back(b);
                SET(b*3001+a);
			}
        }
		int res = 0;
		for(int i = 0; i < v; ++i) {
			for(vector<int>::iterator it = g[i].begin();
                it != g[i].end(); it++)
                for(vector<int>::iterator jt = g[*it].begin();
                jt != g[*it].end(); jt++)
                    if(GET(*jt*3001+i))
                        ++res;
		}
		for(int i = 0; i < v; i++) {
		    for(vector<int>::iterator it = g[i].begin();
                it != g[i].end(); it++)
                    RSET(*it*3001+i);
		}
		printf("%d\n", res);
	}
	return 0;
}
