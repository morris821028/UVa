#include <stdio.h> 
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
	struct Event {
		int x, s, id;
		Event(int a = 0, int b = 0, int c = 0):
			x(a), s(b), id(c) {}
		bool operator<(const Event e) const {
			return x < e.x || (x == e.x && s > e.s);
		}
	};
	struct Elem {
		int y, id;
		Elem(int a = 0, int b = 0):
			y(a), id(b) {}
		bool operator<(const Elem &e) const {
			return y > e.y;
		}
	};
	
    vector< pair<int, int> > getSkyline(vector< vector<int> >& buildings) {
     	vector<Event> timeline;
        multimap<Elem, int> S;
        vector< multimap<Elem, int>::iterator > bit;
        vector< pair<int, int> > ret;
        
        bit.resize(buildings.size());
        
    	int l, r, h;
        for (int i = 0; i < buildings.size(); i++) {
        	l = buildings[i][0], r = buildings[i][1], h = buildings[i][2];
        	timeline.push_back(Event(l, 1, i));
        	timeline.push_back(Event(r, -1, i));
        }
        sort(timeline.begin(), timeline.end());
        
        int f = 0;
        for (int i = 0; i < timeline.size(); ) {
        	int x = timeline[i].x;
        	while (i < timeline.size() && timeline[i].x == x) {
        		int id = timeline[i].id;
        		if (timeline[i].s == 1) {
        			bit[id] = S.insert(make_pair(Elem(buildings[id][2], id), 0));
    	    	} else {
	        		S.erase(bit[id]);
        		}
        		i++;
        	}
        	if (S.size()) {
        		if (f == 0 || ret.back().second != S.begin()->first.y) {
        			f = 1;
        			ret.push_back(make_pair(x, S.begin()->first.y));
        		}
        	} else {
        		if (f == 0 || ret.back().second != 0) {
        			f = 1;
        			ret.push_back(make_pair(x, 0));
        		}
        	}
        }
        return ret;
    }
};

int main() {
	Solution s;
	int A[][3] = { {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8} };
	vector< vector<int> > b;
	for (int i = 0; i < 5; i++) {
		vector<int> v(A[i], A[i]+3);
		b.push_back(v);
	}
	vector< pair<int, int> > ret = s.getSkyline(b);
	for (int i = 0; i < ret.size(); i++)
		printf("%d %d\n", ret[i].first, ret[i].second);
	return 0;
}

