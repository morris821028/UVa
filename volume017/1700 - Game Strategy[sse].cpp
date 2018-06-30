#include <cstdio>
#include <cstring>
using namespace std;

typedef int v4si __attribute__ ((vector_size (16)));

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if (p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while ((c = readchar()) < '-')	{ if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while ((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
inline int ReadStr(char *s) {
	static char c;
	while ((c = readchar()) <= ' ')	{if (c == EOF)	return 0;}
	*s = c, s++;
	while ((c = readchar()) > ' ')
		*s = c, s++;
	*s = '\0';
	return 1;
}

int main() {
	int n, m;
//	while (scanf("%d", &n) == 1) {
	while (ReadInt(&n)) {
		static char cmd[26];
		static __attribute__ ((aligned(16))) int ew[1<<20];
		static int e;
		static int* g[26];
		static int gn[26];
		e = 0;
		for (int i = 0; i < n; i++) {
//			scanf("%d", &m);
			ReadInt(&m);
			g[i] = ew + e, gn[i] = m;
			for (int j = 0; j < m; j++) {
//				scanf("%s", cmd);
				ReadStr(cmd);
				int mask = 0, k;
				for (k = 0; cmd[k]; k++)
					mask |= 1<<(cmd[k]-'a');
				ew[e++] = mask;
			}
			while (e&15)	e++; 
		}
		
		int ret[26][26];
		memset(ret, -1, sizeof(ret));
		for (int goal = 0; goal < n; goal++) {
			int visited = 1<<goal;
			ret[goal][goal] = 0;
			for (int dist = 1; ; dist++) {
				int next = visited;
				for (int i = 0; i < n; i++) {
					if ((visited>>i)&1)
						continue;
					static __attribute__ ((aligned(16))) v4si v4s;
					static __attribute__ ((aligned(16))) v4si v4m;
					int m = gn[i], j = 0, f = 0;
					const int* const ptr = g[i];
					for (j = 0; j+12 <= m; j += 12) {
						v4s = *(v4si *) (ptr + j);
						v4m = (v4s & visited) == v4s;
						v4s = *(v4si *) (ptr + j + 4);
						v4m |= (v4s & visited) == v4s;
						v4s = *(v4si *) (ptr + j + 8);
						v4m |= (v4s & visited) == v4s;
						if (v4m[0] || v4m[1] || v4m[2] || v4m[3]) {
							next |= 1<<i;
							ret[i][goal] = dist;
							f = 1;
							break;
						}
					}
					if (f == 0) {
						for (; j < m; j++) {
							int e = g[i][j];
							if ((visited&e) == e) {
								next |= 1<<i;
								ret[i][goal] = dist;
								break;
							}
						}
					}					
				}
				if (next == visited)
					break;
				visited = next;
			}
		}
		
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				printf("%d%c", ret[i][j], " \n"[j==n-1]);
		}
	}
	return 0;
}
/*
2
2 ab b
1 b
3
1 b
2 b a
2 ab ac
*/
