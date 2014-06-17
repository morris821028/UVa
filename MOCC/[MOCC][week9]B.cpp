// http://cxsjsxmooc.openjudge.cn/
#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;

int main() {
	for(int n, x; scanf("%d", &n) == 1;) {
		char cmd[10];
		multiset<int> S;
		set<int> I;
		while(n--) {
			scanf("%s", cmd);
			if(cmd[0] == 'a' && cmd[1] == 'd') { // add
				scanf("%d", &x);
				I.insert(x);
				S.insert(x);
				printf("%d\n", S.count(x));
			} else if(cmd[0] == 'a' && cmd[1] == 's') { // ask
				scanf("%d", &x);
				printf("%d %d\n", I.find(x) != I.end(), S.count(x));
			} else { // del
				scanf("%d", &x);
				printf("%d\n", S.count(x));
				S.erase(x);
			}
		}
	}
	return 0;
}
