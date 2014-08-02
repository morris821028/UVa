#include <stdio.h>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> getLineToken(char s[]) {
	stringstream sin(s);
	string token;
	vector<string> ret;
	while(sin >> token)
		ret.push_back(token);
	return ret;
}
int main() {
	char s[32767];
	gets(s);
	while(gets(s)) {
		map<string, int> R[26 * 26];
		vector<string> D, C;
		D = getLineToken(s);
		gets(s);
		C = getLineToken(s);
		for(int i = D.size() - 1; i >= 0; i--) {
			int len = D[i].length();
			int h1 = D[i][0] - 'a', h2 = D[i][len-1] - 'a';
			string t = D[i];
			sort(t.begin(), t.end());
			R[h1 * 26 + h2][t] = i;
		}
		for(int i = 0; i < C.size(); i++) {
			int len = C[i].length();
			int h1 = C[i][0] - 'a', h2 = C[i][len-1] - 'a';
			string t = C[i];
			sort(t.begin(), t.end());
			if(R[h1 * 26 + h2].find(t) != R[h1 * 26 + h2].end())
				printf("%s%c", D[R[h1 * 26 + h2][t]].c_str(), i == C.size() - 1 ? '\n' : ' ');
			else
				printf("%s%c", C[i].c_str(), i == C.size() - 1 ? '\n' : ' ');
		}
	}
	return 0;
}
/*
2
make me programming rich will
pagmrnmorig will mkae me rcih
dreaming drinaemg yeah
yaeh right keep drinaemg
*/
