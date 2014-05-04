// http://cxsjsxmooc.openjudge.cn/
#include <stdio.h>
#include <algorithm>
#include <map>
#include <list>
using namespace std;

int main() {
	for(int n; scanf("%d", &n) == 1; )  {
		char cmd[10];
		int id, num, aid;
		map< int, list<int> > S;
		while(n--) {
			scanf("%s", cmd);
			if(cmd[0] == 'n') { // new
				scanf("%d", &id);
				S[id] = list<int>();
			} else if(cmd[0] == 'a') { // add
				scanf("%d %d", &id, &num);
				S[id].push_back(num);
			} else if(cmd[0] == 'm') { // merge
				scanf("%d %d", &id, &aid);
				S[id].merge(S[aid]);
			} else if(cmd[0] == 'u') { // unique
				scanf("%d", &id);
				S[id].sort();
				S[id].unique();
			} else { // out
				scanf("%d", &id);
				S[id].sort();
				list<int>::iterator it, jt;
				it = S[id].begin(), jt = S[id].end();
				int f = 0;
				for(; it != jt; it++) {
					if(f)	putchar(' ');
					f = 1;
					printf("%d", *it);
				}
				puts("");
			}
		}
	}
	return 0;
}
