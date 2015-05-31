#include <bits/stdc++.h>
using namespace std;

class LRUCache {
public:
	unordered_map<int, pair<int, list<int>::iterator> > addr;
	vector<int> mem;
	list<int> 	time;
	int memIdx;
    LRUCache(int capacity) {
        mem.resize(capacity);
        addr.clear(), time.clear();
        memIdx = 0;
    }
    
    int get(int key) {
    	it = addr.find(key);
        if (it == addr.end())
        	return -1;
        updateRecent(it->second.second);
        return mem[it->second.first];
    }
    
    void set(int key, int value) {
        it = addr.find(key);
        if (it == addr.end())	// miss
        	it = addRecent(key);
        it->second.second = updateRecent(it->second.second);
        mem[it->second.first] = value;
    }
private:
	unordered_map<int, pair<int, list<int>::iterator> >::iterator it;
	unordered_map<int, pair<int, list<int>::iterator> >::iterator addRecent(int key) {
		int mpos = -1;
		list<int>::iterator lpos;
		
		if (addr.size() == mem.size() && time.size()) { // replace
			int trash = time.front();
			time.pop_front();
			
			it = addr.find(trash);
			mpos = it->second.first;
			addr.erase(trash);
		} else {						// new
			mpos = memIdx++;
		}
		lpos = time.insert(time.end(), key);
		addr.insert({key, make_pair(mpos, lpos)});
		return addr.find(key);
	}
	list<int>::iterator updateRecent(list<int>::iterator p) {
		int key = *p;
		time.erase(p);
		return time.insert(time.end(), key);
	}
};

//    void test() {
//		printf("%d\n", get(1));
//		set(1, 3);
//		set(2, 5);
//		set(1, 7);
//		set(3, 9);
//		printf("%d\n", get(2));
//		printf("%d\n", get(1));
//		printf("%d\n", get(3));
//		set(5, 11);
//		printf("%d\n", get(2));
//		printf("%d\n", get(1));
//	}
int main() {
	LRUCache t(3);
//	t.test();
	return 0;
}
