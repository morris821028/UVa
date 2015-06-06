#include <stdio.h> 
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class StockManager {
public:
	StockManager() {
		
	}
	void recordStock(const string &sid, int val) {
		cache[sid] = val;
	}
	void topK(int k = -1) {
		if (k < 0)	
			k = vR.size();
		clearCache();
		for (map<int, set<string> >::reverse_iterator it = R.rbegin();
			it != R.rend(); it++) {
			for (auto&x: it->second) {
				printf("%s %d\n", x.c_str(), it->first);
				if (--k == 0)
					return ;
			}
		}
	}
private:
	map<int, set<string> > R;
	unordered_map<string, int> vR;
	unordered_map<string, int> cache;
		
	void updateStock(const string &sid, int val) {
		if (vR.count(sid))
			R[vR[sid]].erase(sid);
		R[val].insert(sid);
		vR[sid] = val;
	}
	void clearCache() {
		for (auto& x: cache)
			updateStock(x.first, x.second);
		cache.clear();
	}
} sm;

void test() {
	StockManager sm;
	sm.recordStock("nico", 20);
	sm.recordStock("inker", 10);
	sm.topK(2);
	sm.recordStock("inker", 30);
	sm.recordStock("morris", 1);
	sm.topK(3);
	sm.recordStock("nico", 10);
	sm.recordStock("morris", 20);
	sm.topK(3);
}
int main() {
	int cmd, val;
	char s[16];
	while (scanf("%d", &cmd) == 1) {
		if (cmd == 1) {
			scanf("%s %d", s, &val);
			sm.recordStock(s, val);
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
