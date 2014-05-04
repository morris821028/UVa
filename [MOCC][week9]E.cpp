// http://cxsjsxmooc.openjudge.cn/
#include <stdio.h>
#include <set>
using namespace std;

int getPF(int n) {
	int ret = 0;
	for(int i = 2; i*i <= n; i++) {
		if(n%i == 0) {
			while(n /= i, n%i == 0);
			ret++;
		}
	}
	if(n != 1 && ret > 0)	ret++;
	return ret;
}
int main() {
	for(int n; scanf("%d", &n) == 1;) {
		multiset< pair<int, int> > S;
		while(n--) {
			for(int i = 0, x; i < 10; i++) {
				scanf("%d", &x);
				S.insert(make_pair(getPF(x), x));
			}			
			multiset< pair<int, int> >::iterator it;
			multiset< pair<int, int> >::iterator jt;
			it = S.begin();
			jt = S.end();
			jt--;
			printf("%d %d\n", (*jt).second, (*it).second);
			S.erase(it);
			S.erase(jt);
		}
	}
	return 0;
}
