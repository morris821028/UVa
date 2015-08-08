#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 1024;

template<typename WTYPE, bool FUNC(WTYPE, WTYPE)>
class MonoQueue {
public:
	deque< pair<int, WTYPE> > Q;
	int K;
	void setWindow(int K) {
		this->K = K;
	}
	inline void add(int idx, WTYPE val) {
		while (!Q.empty() && Q.front().first <= idx - K)
			Q.pop_front();
		while (!Q.empty() && FUNC(val, Q.back().second))
			Q.pop_back();
		Q.push_back({idx, val});
	}
	inline pair<int, WTYPE> top() {
		return Q.front();
	}
};
bool cmp1(int a, int b) { return a > b; }
bool cmp2(int a, int b) { return a < b; }
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
	int N, M, K, val;
	while (ReadInt(&N)) {
		ReadInt(&M);
		ReadInt(&K);
				
		MonoQueue<int, cmp1> mxC[MAXN];
		MonoQueue<int, cmp2> mnC[MAXN];
		for (int i = 0; i < M; i++)
			mxC[i].setWindow(K), mnC[i].setWindow(K);
		int ret = INT_MAX;
		
		for (int i = 0; i < N; i++) {
			MonoQueue<int, cmp1> mxR;
			MonoQueue<int, cmp2> mnR;
			mxR.setWindow(K), mnR.setWindow(K);
			for (int j = 0; j < M; j++) {
				ReadInt(&val);				
				mxC[j].add(i, val);
				mxR.add(j, mxC[j].top().second);
				
				mnC[j].add(i, val);
				mnR.add(j, mnC[j].top().second);
				
				if (i >= K-1 && j >= K-1)
					ret = min(ret, mxR.top().second - mnR.top().second);
			}
		}

		printf("%d\n", ret);
	}
	return 0;
}
