#include <bits/stdc++.h> 
using namespace std;

string toLower(string a) {
	for (int i = 0; i < a.length(); i++)
		a[i] = tolower(a[i]);
	return a;
}

bool cmpStr(string a, string b) {
	return toLower(a) < toLower(b);
}
bool cmp(pair<int, string> &a, pair<int, string> &b) {
	if (a.first != b.first)
		return a.first > b.first;
	return cmpStr(a.second, b.second);
}
int main() {
	int n, cases = 0;
	char s[1024];
	while (scanf("%d", &n) == 1) {
		while (getchar() != '\n');
		vector<pair<int, string>> A;
		A.reserve(n);
		for (int i = 0; i < n; i++) {
			fgets(s, 1024, stdin);
			char *tok = strtok(s, ";");
			string name = tok; tok = strtok(NULL, ";");
			int s = 0;
			while (tok != NULL) {
				int a, b, c, d, e;
				sscanf(tok, "%d %d %d %d %d", &a, &b, &c, &d, &e);
				s += (a+b+c+d)+e*2;
				tok = strtok(NULL, ";");
			}
			A.emplace_back(make_pair(s, name));
		}
		sort(A.begin(), A.end(), cmp);
		printf("Case %d:\n", ++cases);
		for (auto e: A)
			printf("%s %d\n", e.second.c_str(), e.first);
	}
	return 0;
}
/*
3
Michael Jordan;0 1 1 0 1;0 1 1 0 1;0 1 1 0 1;0 0 0 0 1;0 0 0 0 1
Scotty Pippen;0 1 1 0 1;0 1 1 0 1;0 1 1 0 1;0 0 0 0 1;0 0 0 1 1
Charles Barkley;0 1 1 0 1;0 1 1 0 1;0 1 1 0 1;0 0 0 0 1;0 0 1 1 1
*/
