#include <bits/stdc++.h>
using namespace std;

int main() {
	char s1[128], s2[128], s[128];
	map<string, string> R;
	scanf("%*s");
	while (fgets(s, 128, stdin)) {
		int n = strlen(s)-1;
		s[n] = '\0';
		if (!strcmp(s, "[1337]"))
			break;
		for (int i = 0; i < n; i++) {
			if (s[i] == ':') {
				s[i] = '\0';
				R[s] = s+i+1;
				break;
			}
		}
	}
	
	string line;
	while (getline(cin, line)) {
		if (line == "[3ND]")
			break;
		string s;
		stringstream sin(line);
		while (sin >> s) {
			if (!R.count(s))
				cout << s << " ";
			else
				cout << R[s] << " ";
		}
		cout << endl;
	}
	return 0;
}
