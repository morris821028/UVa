#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> 
#include <sstream>
#include <iostream>
using namespace std;

void removeLeading(string &s) {
	while (s.length() > 1 && s[0] == '0')
		s.erase(s.begin());
}
int main() {
	int testcase, cases = 0;
	char s[32767];
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		gets(s);
		stringstream sin(s);
		string token;
		string A[1024];
		int n = 0;
		while (sin >> token) {
			if (token == "not" || token == "shr" || token == "shl")
				A[n++] = token;
			else if (token == "xor" || token == "and" || token == "or")
				A[n++] = token;
			else {
				removeLeading(token);
				while (n > 0) {
					if (A[n-1] == "not" || A[n-1] == "shr" || A[n-1] == "shl") {
						if (A[n-1] == "not") {
							for (int i = 0; i < token.length(); i++)
								token[i] = token[i] == '0' ? '1' : '0';
							removeLeading(token);
						} else if (A[n-1] == "shr") {
							if (token.length() > 1)
								token.erase(token.begin() + token.length() - 1);
							else
								token = "0";
						} else if (A[n-1] == "shl")
							token = token + "0";
						n--;
					} else {
						break;
					}
				}
				A[n++] = token;
			}
		}
		for (int i = 2; i < n; i += 2) {
			int mx = max(A[i].length(), A[0].length());
			A[0] = string(mx - A[0].length(), '0') + A[0];
			A[i] = string(mx - A[i].length(), '0') + A[i];
			if (A[i-1] == "xor") {
				for (int j = 0; j < A[0].length(); j++) {
					A[0][j] = A[0][j] != A[i][j] ? '1' : '0';
				}
			} else if (A[i-1] == "and") {
				for (int j = 0; j < A[0].length(); j++) {
					A[0][j] = A[0][j] == '1' && A[i][j] == '1' ? '1' : '0';
				}				
			} else if (A[i-1] == "or") {
				for (int j = 0; j < A[0].length(); j++) {
					A[0][j] = A[0][j] == '1' || A[i][j] == '1' ? '1' : '0';
				}
			}
		}
		removeLeading(A[0]);
		printf("Case %d: %s\n", ++cases, A[0].c_str());
	}
	return 0;
}
