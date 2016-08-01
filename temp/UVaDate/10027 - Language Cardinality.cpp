#include <bits/stdc++.h> 
using namespace std;

vector< pair<string, string> > rule;
void parseRule(string s) {
	string lhs = "", rhs = "";
	int i = 0;
	while (s[i] != '\"')	i++;
	i++;
	while (s[i] != '\"')
		lhs += s[i], i++;
	i++; 
	while (s[i] != '\"')	i++;
	i++;
	while (s[i] != '\"')
		rhs += s[i], i++;
	rule.push_back(make_pair(lhs, rhs));
}
string parseStart(string s) {
	string ret = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '\"') {
			i++;
			while (s[i] != '\"')
				ret += s[i], i++;
			return ret;
		}
	}
	return ret;
}
void bfs(string st) {
	vector<int> INF(rule.size(), 0);
	for (int i = 0; i < rule.size(); i++) {
		if (rule[i].first == "" && rule[i].second.length() > 0) {
			puts("Too many.");
			return ;
		}
		if (rule[i].first != rule[i].second) {
			size_t pos = rule[i].second.find(rule[i].first);
			if (pos != string::npos)
				INF[i] = 1;
		}
	}
	set<string> S;
	S.insert(st);
	while (true) {
		int update = (int) S.size();
		for (int i = 0; i < rule.size(); i++) {
			for (set<string>::iterator it = S.begin();
				it != S.end(); it++) { 
				string st = *it;
				size_t pos = 0;
				while (pos < st.length()) {
					pos = st.find(rule[i].first, pos);
					if (pos == string::npos)
						break;
					string nt(st);
					nt.erase(pos, rule[i].first.length());
          			nt.insert(pos, rule[i].second);
					S.insert(nt);
					pos++;					
					if (S.size() > 1000 || INF[i]) {
						puts("Too many.");
						return ;
					}					
				}
			}
			if (S.size() != update)
				break;				
		}
		if (S.size() == update)
			break;
	}
	printf("%d\n", (int) S.size());
}
int main() {
	int testcase;
	char s[32767];
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (getchar() != '\n');
	while (testcase--) {
		gets(s);
		string st;
		rule.clear();
		st = parseStart(s);
		while (gets(s) && s[0] != '\0')
			parseRule(s);
		bfs(st);
		if (testcase)
			puts("");
	}
	return 0;
}
/*
999

"AyB"
"A"->"ab"
"Ay"->"cdy"
"B"->"w"
"B"->"x"

"A"
"S"->"aS" 

"SSS"
"SS"->"b"
*/
