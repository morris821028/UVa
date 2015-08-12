#include <bits/stdc++.h> 
using namespace std;

int main() {
	char s[1024], s1[1024], s2[1024];
	string h[] = {"a", "e", "i", "y", "o", "ou"};
	string v[] = {"a", "e", "o"};
	string table[3][10] = {
		{"a", "a", "ai", "a", "w", "w", "w"},
		{"y", "ei", "ei", "y", "ou", "ou", "w"}, 
		{"w", "ou", "oi", "w", "ou", "ou", "w"}
	};
	while (scanf("%s", s) == 1) {
		if (!strcmp(s, "END"))
			break;
		sscanf(s, "%[^-]-%[^-]", s1, s2);
		string a(s1), b(s2);
		string p = a.substr(a.length()-1);
		string q = b.substr(0, 2);
		int x = find(v, v+3, p) - v, y;
		if (q == "ou") {
			y = find(h, h+7, q) - h;
			cout << a.substr(0, a.length()-1) + table[x][y] + b.substr(2) << endl;
		} else {
			q = b.substr(0, 1);
			y = find(h, h+7, q) - h;
			cout << a.substr(0, a.length()-1) + table[x][y] + b.substr(1) << endl;
		}
	}
	return 0;
}
