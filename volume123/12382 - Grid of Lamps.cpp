#include <stdio.h> 
#include <queue>
#include <algorithm>
using namespace std;

int main() {
	int testcase, N, M, x;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &M);
		priority_queue< int, vector<int> > pQN, pQM;
		for(int i = 0; i < N; i++) {
			scanf("%d", &x);
			if(x)	pQN.push(x);
		}
		for(int i = 0; i < M; i++) {
			scanf("%d", &x);
			if(x)	pQM.push(x);
		}
		
		int ret = 0;
		while(!pQN.empty()) {
			int r = pQN.top();
			pQN.pop();
			queue<int> tmp;
			while(r && !pQM.empty()) {
				int c = pQM.top();
				pQM.pop();
				c--, r--, ret++;
				if(c)
					tmp.push(c);
			}
			ret += r;
			while(!tmp.empty()) {
				pQM.push(tmp.front());
				tmp.pop();
			}
		}
		while(!pQM.empty()) {
			int c = pQM.top();
			pQM.pop();
			ret += c;
		}
		printf("%d\n", ret);
	}
	return 0;
}
