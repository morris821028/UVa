#include <stdio.h> 
#include <algorithm>
#include <map>
using namespace std;
#define maxN 10005
int A[maxN], LDS[maxN];
int BIT[maxN];
void modify(int i, int val, int L) {
	while(i <= L) {
		BIT[i] = max(BIT[i], val);
		i += i&(-i);
	}
}
int query(int i) {
	int ret = 0;
	while(i) {
		ret = max(ret, BIT[i]);
		i -= i&(-i);
	}
	return ret;
}
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
	int N, Q, M, u;
	int cases = 0;
	while(ReadInt(&N) && ReadInt(&Q) && N+Q) {
		map<int, int> R;
		for(int i = 0; i < N; i++) {
			ReadInt(A+i);
			R[A[i]] = 0;
		}
		for(int i = 1; i <= N; i++)
			BIT[i] = 0;
			
		int size = R.size();
		for(map<int, int>::iterator it = R.begin();
			it != R.end(); it++) {
			it->second = size--;
		}
		/* reverse LDS with ending at i-th element */
		int maxLDS = 0;
		for(int i = N-1; i >= 0; i--) {
			LDS[i] = query((u = R[A[i]]) - 1) + 1;
			modify(u, LDS[i], R.size());
			maxLDS = max(maxLDS, LDS[i]);
		}
		printf("Set %d:\n", ++cases);
		for(int i = 1; i <= Q; i++) {
			ReadInt(&M);
			printf("  Subset %d:\n", i);
			if(M > maxLDS) {
				printf("    Impossible\n");
				continue;
			}
			printf("   ");
			int prevA = -0x3f3f3f3f;
			for(int j = 0; j < N && M; j++) {
				if(LDS[j] >= M && prevA < A[j]) {
					printf(" %d", A[j]);
					M--, prevA = A[j];
				}
			}
			puts("");
		}
	}
	return 0;
}
/*
6 3
3 4 1 2 3 6
6
4
5
6 2
2 4 6 1 3 5
3
4
0 0 
*/
