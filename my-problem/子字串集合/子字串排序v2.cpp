#include <bits/stdc++.h> 
using namespace std;
char s[512];
struct cmp {
	bool operator() (const pair<int, int> &a, const pair<int, int> &b) const {
		for (int i = 0; i < a.second && i < b.second; i++) {
			if (s[a.first+i] != s[b.first+i])
				return s[a.first+i] < s[b.first+i];
		}
		return a.second < b.second;
	}
};
int main() {
	while (scanf("%s", s) == 1) {
		set< pair<int, int>, cmp > S;
		int n = strlen(s);
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				S.insert({i, j-i+1});
			}
		}
		for (auto &x : S) {
			int base = x.first, len = x.second;
			char c = s[base+len];
			s[base+len] = '\0';
			puts(s + base);
			s[base+len] = c;
		}
	}
	return 0;
}
