#include <stdio.h> 
#include <vector>
using namespace std;

int main() {
	int testcase, cases = 0, N, x;
	scanf("%d", &testcase);
	while (testcase--) { 
		scanf("%d", &N);
		
		vector<int> ret;
		for (int i = 0; i < N; i++) {
			scanf("%d", &x);
			while (ret.size() > 0 && ret.size() - 1 + N - i >= 11 && ret.back() < x)
				ret.pop_back();
			ret.push_back(x);
		}
		
		printf("Case %d:", ++cases);
		if (ret.size() < 11)
			puts(" go home!");
		else {
			for (int i = 0; i < 11; i++)
				printf(" %d", ret[i]);
			puts("");
		}
	} 
	return 0;
}
