#include <bits/stdc++.h> 
using namespace std;

int main() {
	char s[512];
	while (scanf("%s", s) == 1) {
		set<string> S;
		int n = strlen(s);
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				char c = s[j+1];
				s[j+1] = '\0';
				S.insert(s+i);
				s[j+1] = c;
			}
		}
		for (auto &x : S)
			puts(x.c_str());
	}
	return 0;
}
