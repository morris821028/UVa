#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	int n, b, f;
	cin >> testcase;
	while (testcase--) {
		cin >> n >> b >> f;
		static string test[16];
		static string res[16];
		for (int i = 0; i < f; ) {
			int ff = 1<<i, idx = 0;
			test[i] = "";
			while (idx < n) {
				for (int j = 0; j < ff && idx < n; j++)
					test[i] += "0", idx++;
				for (int j = 0; j < ff && idx < n; j++)
					test[i] += "1", idx++;
			}
			cout << test[i] << endl << std::flush;
			cin >> res[i];
			i++;
		}
		
		vector<int> broken;
		for (int i = 0, j = 0; i < n; i++) {
			int match = 1;
			if (j < n-b)
			for (int k = 0; k < f && match; k++)
				match &= test[k][i] == res[k][j];
			if (match && j < n-b) {
				j++;
			} else {
				broken.push_back(i);
			}
		}

		for (int i = 0; i < broken.size(); i++) {
			cout << broken[i];
			if (i == broken.size()-1)
				cout << endl << std::flush;
			else
				cout << " ";
		}
		int ac;
		cin >> ac;
		if (ac != 1)
			return -1;
	}
	return 0;
}
