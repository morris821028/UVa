#include <stdio.h> 
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main() {
	int x, y;
	while (scanf("%d %d", &x, &y) == 2) {
		if (x > y)	swap(x, y);
		vector< pair<int, int> > D;
		set<int> S;
		set< pair<int, int> > R;
		D.push_back(make_pair(x, y));
		for (int i = 0; i < 5; i++) {
			scanf("%d %d", &x, &y);
			if (x > y)	swap(x, y);
			D.push_back(make_pair(x, y));			
		}
		sort(D.begin(), D.end());
		for (int i = 0; i < 6; i++) {
			S.insert(D[i].first);
			S.insert(D[i].second);
			R.insert(D[i]);
		} 
		int ok = 1;
		ok &= D[0] == D[1];
		ok &= D[2] == D[3];
		ok &= D[4] == D[5];
		ok &= S.size() <= 3;
		for (set<int>::iterator it = S.begin(), jt;
			it != S.end(); it++) {
			for (jt = it, jt++; jt != S.end(); jt++) {
				if (R.find(make_pair(*it, *jt)) == R.end())
					ok = 0;
			}
		}
		puts(ok ? "POSSIBLE" : "IMPOSSIBLE");
	}
	return 0;
}
