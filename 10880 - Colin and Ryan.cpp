#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

int main() {
	int cases; cin >> cases;
	for (int C, R, c = 1; cases--; ++c) {
		cin >> C >> R;
		set<int> res;
		int diff = C - R;
		cout << "Case #" << c << ":";
		if (diff == 0) {
			cout << " 0" << endl;
			continue;
		}
		for (int i = 1; i * i <= diff; ++i)
			if (diff % i == 0) {
				res.insert(diff / i);
				res.insert(i);
			}
		for (set<int>::iterator it = res.begin(); it != res.end(); it++)
			if (*it > R) cout << " " << *it;
		cout << endl;
	}
	return 0;
}
