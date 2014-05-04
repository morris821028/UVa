#include <stdio.h>
#include <set>
using namespace std;

int main() {
	int n, x[100005];
	while(scanf("%d", &n) == 1) {
		int sum = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d", &x[i]);
			sum += x[i];
		}
		if(sum%3) {
			puts("0");
			continue;
		}
		int e = sum / 3;
		set<int> S;
		for(int i = 0, s = 0; i < n; i++) {
			s += x[i], s %= sum;
			S.insert(s);
		}
		int ret = 0;
		for(int i = 0, s = 0; i < n; i++) {
			s += x[i];
			if(S.find((s + e)%sum) != S.end() &&
				S.find((s + 2*e)%sum) != S.end())
				ret++;
		}
		printf("%d\n", ret / 3);
	}
	return 0;
}
