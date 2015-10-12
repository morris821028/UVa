#include <bits/stdc++.h> 
using namespace std;
int main() {
	string line;
	list<string> ls;
	while (getline(cin, line)) {
		if (line == "0")
			break;
		for (int i = 0; i < line.length(); i++) {
			if (isalpha(line[i])) {
				string s = ""; 
				while (i < line.length() && isalpha(line[i]))
					s += line[i], i++;
				i--;
				int idx = 1, id = -1;
				for (list<string>::iterator it = ls.begin();
					it != ls.end(); it++, idx++) {
					if (*it == s) {
						id = idx;
						ls.erase(it);
						break;
					}
				}
				if (id == -1) {
					printf("%s", s.c_str());
				} else {
					printf("%d", id);
				}
				ls.push_front(s);
			} else {
				putchar(line[i]);
			}
		}
		puts("");
	}
	return 0;
}
