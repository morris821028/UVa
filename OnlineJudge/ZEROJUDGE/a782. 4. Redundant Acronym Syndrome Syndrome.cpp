#include <bits/stdc++.h>
using namespace std;

int main() {
	string line, x;
	while (getline(cin, line)) {
		if (line == "END")
			break;
		stringstream sin(line);
		vector<string> A;
		while (sin >> x)
			A.push_back(x);
		string S = "";
		for (int i = 0; i < A.size(); i++)
			S += toupper(A[i][0]);
		cout << S << " " << A.back() << endl;
	}
	return 0;
}
