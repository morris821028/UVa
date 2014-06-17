// http://cxsjsxmooc.openjudge.cn/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <queue>
#include <ctype.h>
using namespace std;

char s[32][512], lineStr[1024];
string str[32];
int strSize;
queue<string> tokenQ;
int str2num(string s) {
	return atoi(s.c_str());
}
string num2str(int n) {
  	string s;
  	stringstream ss(s);
  	ss << n;
	return ss.str();
}
int isValidNum(string s) {
	int ret = 0;
	for(int i = 0; i < s.length(); i++) {
		if(!isdigit(s[i]))
			return -1;
		ret = ret * 10 + s[i] - '0';
		if(ret > 99999)
			return -1;
	}
	return ret;
}
string parsing() {
	string p = tokenQ.front();
	tokenQ.pop();
	if(p == "copy")  {
		string N, X, L;
		int n, x, l;
		if(tokenQ.front() == "find" || tokenQ.front() == "rfind") {
			N = parsing();
		} else {
			N = tokenQ.front(), tokenQ.pop();
		}
		if(tokenQ.front() == "find" || tokenQ.front() == "rfind") {
			X = parsing();
		} else {
			X = tokenQ.front(), tokenQ.pop();
		}
		if(tokenQ.front() == "find" || tokenQ.front() == "rfind") {
			L = parsing();
		} else {
			L = tokenQ.front(), tokenQ.pop();
		}
		n = str2num(N), x = str2num(X), l = str2num(L);
		
		return str[n].substr(x, l);
	} else if(p == "add") {
		string S1, S2;
		int s1, s2;
		if(tokenQ.front() == "copy" || tokenQ.front() == "add") {
			S1 = parsing();
		} else {
			S1 = tokenQ.front(), tokenQ.pop();
		}
		if(tokenQ.front() == "copy" || tokenQ.front() == "add") {
			S2 = parsing();
		} else {
			S2 = tokenQ.front(), tokenQ.pop();
		}
		s1 = isValidNum(S1), s2 = isValidNum(S2);
		if(s1 < 0 || s2 < 0)
			return S1 + S2;
		else
			return num2str(s1 + s2);
	} else if(p == "find") {
		string S, N;
		int s, n;
		if(tokenQ.front() == "copy" || tokenQ.front() == "add") {
			S = parsing();
		} else {
			S = tokenQ.front(), tokenQ.pop();
		}
		if(tokenQ.front() == "find" || tokenQ.front() == "rfind") {
			N = parsing();
		} else {
			N = tokenQ.front(), tokenQ.pop();
		}
		n = str2num(N);
		int pos = str[n].find(S);
		
		if(pos != string::npos) {
			return num2str(pos);
		} else {
			return num2str(str[n].length());
		}
	} else if(p == "rfind") {
		string S, N;
		int s, n;
		if(tokenQ.front() == "copy" || tokenQ.front() == "add") {
			S = parsing();
		} else {
			S = tokenQ.front(), tokenQ.pop();
		}
		if(tokenQ.front() == "find" || tokenQ.front() == "rfind") {
			N = parsing();
		} else {
			N = tokenQ.front(), tokenQ.pop();
		}
		n = str2num(N);
		int pos = str[n].rfind(S);
		if(pos != string::npos) {
			return num2str(pos);
		} else {
			return num2str(str[n].length());
		}
	} else if(p == "insert") {
		string S, N, X;
		int s, n, x;
		if(tokenQ.front() == "copy" || tokenQ.front() == "add") {
			S = parsing();
		} else {
			S = tokenQ.front(), tokenQ.pop();
		}
		if(tokenQ.front() == "find" || tokenQ.front() == "rfind") {
			N = parsing();
		} else {
			N = tokenQ.front(), tokenQ.pop();
		}
		if(tokenQ.front() == "find" || tokenQ.front() == "rfind") {
			X = parsing();
		} else {
			X = tokenQ.front(), tokenQ.pop();
		}
		n = str2num(N), x = str2num(X);
		str[n].insert(x, S);
	} else if(p == "reset") {
		string S, N, X;
		int s, n, x;
		if(tokenQ.front() == "copy" || tokenQ.front() == "add") {
			S = parsing();
		} else {
			S = tokenQ.front(), tokenQ.pop();
		}
		if(tokenQ.front() == "find" || tokenQ.front() == "rfind") {
			N = parsing();
		} else {
			N = tokenQ.front(), tokenQ.pop();
		}
		n = str2num(N);
		str[n] = S;
	} else if(p == "print") {
		string S, N, X;
		int s, n, x;
		if(tokenQ.front() == "find" || tokenQ.front() == "rfind") {
			N = parsing();
		} else {
			N = tokenQ.front(), tokenQ.pop();
		}
		n = str2num(N);
		printf("%s\n", str[n].c_str());
	} else if(p == "printall") {
		for(int i = 1; i <= strSize; i++)
			printf("%s\n", str[i].c_str());
	} else if(p == "over") {
		
	}
	return "";
}
int main() {
	for(int n; scanf("%d", &n) == 1;) {
		int N, X, L, S1, S2, S;
		for(int i = 1; i <= n; i++) {
			scanf("%s", s[i]);
			str[i] = s[i];
		}
		strSize = n;
		while(getchar() != '\n');
		while(gets(lineStr)) {
			stringstream sin(lineStr);
			string token;
			while(sin >> token)
				tokenQ.push(token);
			parsing();
		}
	}
	return 0;
}
