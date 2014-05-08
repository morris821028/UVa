#include <stdio.h>
#include <set>
using namespace std;

int main() {
	scanf("%*d");
	for(int n, m, x; scanf("%d %d", &n, &m) == 2;) {
		set<int> A, B;
		A.insert(0);
		for(int i = 0; i < n; i++) {
			scanf("%d", &x);
			B = A;
			for(set<int>::iterator it = A.begin();
				it != A.end(); it++) {
				if(*it + x <= 200000)
				B.insert(*it + x);
			}
			A = B;
		}
		int ret = 0;
		while(m--) {
			scanf("%d", &x);
			ret += A.find(x) != A.end();
		}
		printf("%d\n", ret);
	}
	return 0;
}
