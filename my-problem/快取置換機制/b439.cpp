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
    LRUCache(int capacity) {
    	size = capacity;
        mem.resize(capacity, 0);
        addr.clear(), time.clear();
        memIdx = 0;
    }
    
    pair<int, int> get(int key) {
    	it = addr.find(key);
        if (it == addr.end())
			it = replace(key), mem[it->second.first] = 0;
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
	int M, cmd, x, y;
	pair<int, int> t;
	scanf("%d", &M);
	
	LRUCache LL(M);
	while (scanf("%d", &cmd) == 1) {
		if (cmd == 0) {
			scanf("%d", &x);
			pair<int, int> t = LL.get(x);
			printf("%d %d\n", t.first, t.second);
		} else {
			scanf("%d %d", &x, &y);
			LL.set(x, y);
		}
	}
	return 0;
}
