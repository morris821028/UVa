#include <stdio.h> 
#include <vector>
#include <string.h>
#include <algorithm>
#include <set>
#include <iostream>
#include <sstream>
using namespace std;
template <typename T>
  string NumberToString ( T Number )
  {
     ostringstream ss;
     ss << Number;
     return ss.str();
  }
const int mod = 1000000;
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("bout.txt", "w+t", stdout);
	int testcase, n, m, x, y;
	int cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		vector< pair<int, int> > D;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			D.push_back(make_pair(x, y));
		}
		sort(D.begin(), D.end());
		int ret = 0, A[30];
		set<string> S;
		for (int i = (1<<n)-1; i >= 0; i--) {
			int peak = 0, p = 0;
			for (int j = 0; j < n; j++) {
				if ((i>>j)&1)
					A[p++] = j;
			}
			int ok = 1;
			for (int j = 1; j < p; j++)
				if (D[A[j]].second == D[A[j-1]].second)
					ok = 0;
			if (!ok)	continue;
			for (int j = 1; j < p - 1; j++) {
				if (D[A[j-1]].second < D[A[j]].second &&
					D[A[j+1]].second < D[A[j]].second)
					peak++;
				if (D[A[j-1]].second > D[A[j]].second &&
					D[A[j+1]].second > D[A[j]].second)
					peak++;
			}
			if (peak == m) {
				string path = "";
				for (int j = 0; j < p; j++)
					path += NumberToString(D[A[j]].second) + " ";
				S.insert(path);
			}
		}
		ret = S.size();
		printf("Case %d: %d\n", ++cases, ret%mod);
	}
	return 0;
}
