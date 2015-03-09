// http://cxsjsxmooc.openjudge.cn/
#include <stdio.h>
#include <stdlib.h>
#include <set>
using namespace std;

int main() {
#define oo 0x3f3f3f3f
	for(int n, id, power; scanf("%d", &n) == 1;) {
		set< pair<int, int> > S;
		S.insert(make_pair(1000000000, 1));
		for(int i = 0; i < n; i++)	 {
			scanf("%d %d", &id, &power);
			S.insert(make_pair(power, id));
			set< pair<int, int> >::iterator it;
			it = S.find(make_pair(power, id));
			pair<int, int> f1, f2;
			f1 = make_pair(-oo, 0);
			f2 = make_pair(oo, 0);
			if(it != S.begin()) {
				it--;
				f1 = *it;
				it++;
			}
			if(it != S.end()) {
				it++;
				f2 = *it;
				it--;
			}
			if(abs(f2.first - power) < abs(f1.first - power))
				f1 = f2;
			printf("%d %d\n", id, f1.second);
		}
	}	
	return 0;
}
