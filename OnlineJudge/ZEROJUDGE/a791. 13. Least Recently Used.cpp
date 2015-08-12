#include <bits/stdc++.h>
using namespace std;
typedef pair<int, list<int>::iterator> PIT_TYPE;
typedef unordered_map<int, pair<int, list<int>::iterator> >::iterator HIT_TYPE;
class LRUCache {
public:	
	int memIdx, size;
	list<int> time;
	vector<int> mem;
	unordered_map<int, PIT_TYPE> addr;
	int miss;
    LRUCache(int capacity) {
    	size = capacity;
        mem.resize(capacity, 0);
        addr.clear(), time.clear();
        memIdx = 0;
        miss = 0;
    }
    
    pair<int, int> get(int key) {
    	it = addr.find(key);
        if (it == addr.end())
			it = replace(key), mem[it->second.first] = 0, miss++;
        it->second.second = recent(it->second.second);
        return make_pair(it->second.first, mem[it->second.first]);
    }
    
    HIT_TYPE set(int key, int value) {
        it = addr.find(key);
        if (it == addr.end())
        	it = replace(key);
        it->second.second = recent(it->second.second);
        mem[it->second.first] = value;
        return it;
    }
private:
	HIT_TYPE it;
	HIT_TYPE replace(int key) {
		int mpos = -1, trash;
		list<int>::iterator lpos;
		if (addr.size() == size) {
			trash = time.front(), time.pop_front();
			it = addr.find(trash);
			mpos = it->second.first;
			addr.erase(it);
		} else {
			mpos = memIdx++;
		}
		lpos = time.insert(time.end(), key);
		return addr.insert({key, make_pair(mpos, lpos)}).first;
	}
	list<int>::iterator recent(list<int>::iterator p) {
		int key = *p;
		time.erase(p);
		return time.insert(time.end(), key);
	}
};
int main() {
	LRUCache LL(16);
	int TOT = 0;
	while (true) {
		int x;
		for (int i = 0; i < 20; i++) {
			if (scanf("%d", &x) != 1)
				return 0;
			LL.get(x), TOT++;
		}
		double p = (TOT - LL.miss)*100.0 / TOT;
		printf("cache hit rate: %.2lf%%\n", p);
	}
	return 0;
}
