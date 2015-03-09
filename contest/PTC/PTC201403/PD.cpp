#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	int n;
	while(scanf("%d", &n) == 1 && n) {
		int A[105], B[105];
		for(int i = 0; i < n; i++) {
			scanf("%d %d", &A[i], &B[i]);
		} 
		vector<pair<int, int> > D;
		int mx = 0, rr = 0;
		for(int i = 0; i < n; i++) {
			int ss = 0;
			for(int j = 0; j < n; j++) {
				if(A[i] < A[j] && B[i] < B[j])
					ss++;
			}
			int ww = 0;
			for(int j = 0; j < n; j++) {
				if(A[j] < A[i] && B[j] < B[i])
					ww++;
			}
			if(ss == 0) {
				rr++;
			}
			if(ww > mx)	D.clear(), mx = ww;
			if(mx == ww)
				D.push_back(make_pair(A[i], B[i]));
		}
		printf("%d ", rr);
		if(mx == 0)	D.clear();
		sort(D.begin(), D.end());
		if(D.size())
			printf("%d %d\n", D[D.size()-1].first, D[D.size()-1].second);
		else
			puts("0 0");
	}
	return 0;
}
