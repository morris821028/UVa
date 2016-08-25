#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

const int maxn = 1000001;
int snowflakes[maxn];
int n;
set<int> snow;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int cas;
	cin >> cas;
	while (cas--){
		int maxSnow = 0;
		int l = 0, r = 0;
		snow.clear();
		cin >> n;
		for (int i = 0; i < n; ++i){
			cin >> snowflakes[i];
		}

		while (r < n){
			while (r < n && !snow.count(snowflakes[r]))
				snow.insert(snowflakes[r++]);
			maxSnow = max(maxSnow, r - l);
			snow.erase(snowflakes[l++]);
		}
		cout << maxSnow << '\n';
	}
	return 0;
}
