#include <stdio.h> 
#include <algorithm>
#include <string.h>
#include <iostream>
#include <sstream>
#include <ctype.h>
using namespace std;

int isValidString(string s, int limit) {
	int ok = 1;
	for (int i = 0; i < s.length(); i++)
		ok &= 'a' <= s[i] && s[i] <= 'z';
	return ok && s.length() <= limit;
}
int isValidInteger(string s) {
	int ok = 1, num = 0;
	for (int i = 0; i < s.length(); i++) {
		ok &= isdigit(s[i]);
		if (isdigit(s[i])) {
			num = num * 10 + s[i] - '0';
			if (num > 1000)
				return 0;
		}
	}
	return ok;
}
int ispalindrome(string s) {
	for (int i = 0, j = s.length() - 1; i < j; i++, j--)
		if (s[i] != s[j])
			return 0;
	return 1;
}
int allLetterIn(string s1, string s2) {
	int c[128] = {};
	for (int i = 0; i < s1.length(); i++)
		c[s1[i]] = 1;
	for (int i = 0; i < s2.length(); i++)
		c[s2[i]] = 0;
	for (int i = 0; i < 128; i++)
		if (c[i] > 0)
			return 0;
	return 1;
}
int checkfrequency(string s1, string s2) {
	int c[128] = {};
	for (int i = 0; i < s1.length(); i++)
		c[s1[i]]++;
	for (int i = 0; i < s2.length(); i++)
		c[s2[i]]--;
	for (int i = 0; i < 128; i++)
		if (c[i] > 0)
			return 0;
	return 1;
}
int checkBuild(string s1, string s2) {
	int idx = 0;
	for (int i = 0; i < s2.length() && idx < s1.length(); i++) {
		if (s1[idx] == s2[i])
			idx++;
	}
	return idx == s1.length();
}
int checkCond6(string s1, string s2, string s3) {
	stringstream sin(s2);
	int n;
	sin >> n;
	return s1.length() + n == s3.length();
}
int checkCond7(string s1, string s2) {
	stringstream sin(s2);
	int n;
	sin >> n;
	return s1.length() > n;
}
int main() {
	string s1, s2, s3;
	char line[32767];
	while (gets(line)) {
		s1 = s2 = s3 = "";
		int n = 0;
		for (int i = 0; line[i]; i++) {
			if (line[i] == ' ')
				n++;
			else {
				if (n == 0)	s1 += line[i];
				if (n == 1)	s2 += line[i];
				if (n == 2)	s3 += line[i];
			}
		}
		if (n != 2) {
			puts("FFFFFFF The solution is not accepted");
			continue;
		}
		int P[10];
		P[0] = isValidString(s1, 1000) && isValidString(s3, 2000) && isValidInteger(s2);
		P[1] = P[0] && ispalindrome(s3);
		P[2] = P[0] && allLetterIn(s1, s3);
		P[3] = P[0] && checkfrequency(s1, s3);
		P[4] = P[0] && checkBuild(s1, s3);
		P[5] = P[0] && checkCond6(s1, s2, s3);
		P[6] = P[0] && checkCond7(s1, s2);
		int ok = 1;
		for (int i = 0; i < 7; i++) {
			printf("%c", P[i] ? 'T' : 'F');
			ok &= P[i];
		}
		printf(" The solution is %saccepted\n", ok ? "" : "not ");
	}
	return 0;
}
