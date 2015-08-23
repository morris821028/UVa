#include <bits/stdc++.h> 
using namespace std;

int main() {
	list<string> A;
	string cmd, X, N;
	while (cin >> cmd) {
		if (cmd == "ADD") {
			cin >> X;
			A.push_back(X);
		} else if (cmd == "INSERT") {
			cin >> X >> N;
			list<string>::iterator it = find(A.begin(), A.end(), N);
			A.insert(it, X);
		} else if (cmd == "REMOVE") {
			cin >> X;
			list<string>::iterator it = find(A.begin(), A.end(), X);
			A.erase(it);
		} else {
			for (auto &x : A)
				cout << x << " ";
			cout << endl;
		}
	}
	return 0;
}
