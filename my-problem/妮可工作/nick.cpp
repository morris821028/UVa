#include <stdio.h> 
#include <map>
#include <set>
#include <vector>
#include <iostream>
using namespace std;

class StockManager {
public:
	StockManager() {
		
	}
	int updateStock(string sid, int val) {
		if (vR.count(sid))
			R[vR[sid]].erase(sid);
		R[val].insert(sid);
		vR[sid] = val;
	}
	void topK(int k = -1) {
		if (k < 0)	
			k = vR.size();
		for (map<int, set<string> >::reverse_iterator it = R.rbegin();
			it != R.rend(); it++) {
			for (set<string>::iterator jt = it->second.begin();
				jt != it->second.end(); jt++) {
				printf("%s %d\n", jt->c_str(), it->first);
				if (--k == 0)
					return ;
			}
		}
	}
private:
	map<int, set<string> > R;
	map<string, int> vR;
} sm;
int main() {
	int cmd, val;
	char s[16];
	while (scanf("%d", &cmd) == 1) {
		if (cmd == 1) {
			scanf("%s %d", s, &val);
			sm.updateStock(s, val);
		} else {
			scanf("%d", &val);
			sm.topK(val);
			puts("");
		}
	}
	return 0;
}
/*

*/
