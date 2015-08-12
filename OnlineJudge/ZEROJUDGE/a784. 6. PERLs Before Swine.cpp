#include <bits/stdc++.h>
using namespace std;

int main() {
	string x;
	while (getline(cin, x)) {
		string suffix = "", prefix = "";
		for (int i = 0, p = 0, f = 0; i < x.length(); i++) {
			if (p >= 1)	f = 1;
			if (p == 0 && f == 1) {
				for (i++; x[i] != ';' && i < x.length(); i++)
					prefix += x[i];
				break;
			}
			if (x[i] == '(')	p++;
			if (x[i] == ')')	p--;
			suffix += x[i];
		}
		cout << prefix << " " << suffix << ";" << endl;
	}
	return 0;
}
