#include <bits/stdc++.h>
using namespace std;
vector<string> dict;
int diff(string a, string b) {
	int i = 0, j = 0;
	while (i < a.length() && j < b.length()) {
		if (a[i] != b[j])	i++;
		else				i++, j++;
	}
	if (j == b.length())	return a.length() - b.length();
	return -1;
}
int main() {
	char s[1024], c;
	while (scanf("%s", s) == 1) {
		if (s[0] == '|')
			break;
		dict.push_back(s);
	}
	while (isspace(c = getchar()));
	ungetc(c, stdin);
	
	string line;
	while (getline(cin, line)) {
		string token = "";
		for (int i = 0; i < line.length(); i++) {
			if (isalpha(line[i])) {
				token += line[i];
			} else {
				if (token != "") {
					int mm = INT_MAX, kd = 0, is = 0;
					for (int i = 0; i < dict.size(); i++) {
						int d = diff(dict[i], token);
						if (d == -1)
							continue;
						if (d < mm)	mm = d, kd = 0, is = i;
						if (d == mm)	kd++;
					}
					if (kd == 1)
						cout << dict[is];
					else
						cout << token; 
				}
				token = "";
				cout << line[i];
			}
		}
		cout << endl;
	}
	return 0;
}
