#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int N, A[65536], cases = 0;
	while(scanf("%d", &N) == 1 && N) {
		for(int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		sort(A, A+N);
		
		long long ret = 0;
		for(int i = 1, j = 0; i < N; i++) {
			while(A[j] < A[i])
				j++;
			ret += j;
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
