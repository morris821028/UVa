#include <stdio.h> 
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <ctype.h>
using namespace std;
vector<string> toToken(string s) {
	stringstream sin(s);
	string token;
	vector<string> r;
	while (sin >> token)
		r.push_back(token);
	return r;
}
int isConsonant(char c) {
	c = tolower(c);
	if (c == 'a')	return 0;
	if (c == 'e')	return 0;
	if (c == 'i')	return 0;
	if (c == 'o')	return 0;
	if (c == 'u')	return 0;
	if (c == 'y')	return 0;
	return 1;
} 
int checkCond1(vector<string> &t) {
	for (int i = 0; i < t.size(); i++) {
		int c = 0;
		for (int j = 0; j < t[i].length(); j++) {
			if (isConsonant(t[i][j]))
				c++;
			else
				c = 0;
			if (c > 5)	return 0;
		}
	}
	return 1;
}
int checkCond2(vector<string> &t, vector<int> &D2) {
	int A = 0, B = 0;
	for (int i = 0; i < t.size(); i++) {
		int c = 0;
		for (int j = 0; j < t[i].length(); j++) {
			if (isConsonant(t[i][j]))
				c++;
			else
				c = 0;
			if (c > 4)	A = 1;
		}
	}
	for (int i = D2.size() - 1; i >= max(0, (int) D2.size() - 10); i--) {
		if (D2[i] > 0)
			B++;
	}
	return !(A && B > 2);
}
int checkCond3(string s, vector<string> &D3) {
	int A = 0;
	for (int i = D3.size() - 1; i >= max(0, (int) D3.size() - 10); i--) {
		if (D3[i] == s)
			A++;
		if (A > 1)
			return 0;
	}
	return 1;
}
int count4(vector<string> &t) {
	int A = 0;
	for (int i = 0; i < t.size(); i++) {
		int c = 0;
		for (int j = 0; j < t[i].length(); j++) {
			if (isConsonant(t[i][j]))
				c++;
			else
				c = 0;
			if (c > 4)	A = 1;
		}
	}
	return A;
}
int main() {
	int n;
	char s[256];
	while (scanf("%d", &n) == 1) {
		while (getchar() != '\n');
		vector< vector<string> > D;
		vector<int> D2;
		vector<string> D3;
		for (int i = 0; i < n; i++) { 
			gets(s);
			vector<string> t = toToken(s);
			int ok = 1;
			if (!checkCond1(t))
				ok = 0;
			else if (!checkCond2(t, D2))
				ok = 0;
			else if (!checkCond3(s, D3)) 
				ok = 0;
			D.push_back(t), D2.push_back(count4(t)), D3.push_back(s);
			puts(ok ? "y" : "n");
		} 
	}
	return 0;
}
