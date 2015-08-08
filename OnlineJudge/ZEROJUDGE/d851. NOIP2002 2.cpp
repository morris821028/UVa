#include <bits/stdc++.h>
using namespace std;
string S, T, R[1024][2];
int n;
int DBFS() {
	if (S == T)	return 0;
	map<string, int> RF, RB;
	queue< pair<string, int> > QF, QB;
	RF[S] = 0, RB[T] = 0;
	QF.push({S, 0}), QB.push({T, 0});
	while (!QF.empty() || !QB.empty()) {
		pair<string, int> u, v;
		string x, y;
		u = QF.empty() ? make_pair("", INT_MAX) : QF.front(), v = QB.empty() ? make_pair("", INT_MAX) : QB.front();
		if (u.second <= v.second) {
			QF.pop();
			if (u.second >= 5)	return -1;
			x = u.first;
			for (int i = 0; i < x.length(); i++) {
				for (int j = 0; j < n; j++) {
					if (i+R[j][0].length()-1 >= x.length())
						continue;
					int m = 1;
					for (int k = 0; k < R[j][0].length() && m; k++)
						m &= R[j][0][k] == x[i+k];
					if (m) {
						y = x;
						y = y.replace(i, R[j][0].length(), R[j][1]);
						if (RB.count(y))
							return RB[y] + 1 + u.second;
						if (!RF.count(y)) {
							RF[y] = u.second + 1;
							QF.push({y, u.second+1});
						}
					}
				}
			}
		} else {
			u = v;
			QB.pop();
			if (u.second >= 5)	return -1;
			x = u.first;
			for (int i = 0; i < x.length(); i++) {
				for (int j = 0; j < n; j++) {
					if (i+R[j][1].length()-1 >= x.length())
						continue;
					int m = 1;
					for (int k = 0; k < R[j][1].length() && m; k++)
						m &= R[j][1][k] == x[i+k];
					if (m) {
						y = x;
						y = y.replace(i, R[j][1].length(), R[j][0]);
						if (RF.count(y))
							return RF[y] + 1 + u.second;
						if (!RB.count(y)) {
							RB[y] = u.second + 1;
							QB.push({y, u.second+1});
						}
					}
				}
			}
		}
	}
	return -1;
}
int main() {
	cin >> S >> T;
	for (n = 0; cin >> R[n][0] >> R[n][1]; n++);
	
	int ret = DBFS();
	if (ret == -1)
		puts("no answer!");
	else
		printf("%d\n", ret);
	return 0;
}
