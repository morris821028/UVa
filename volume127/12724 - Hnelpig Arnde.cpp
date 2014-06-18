#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
	int testcase, cases = 0;
	int n, m;
	char token[128];
	char lines[4096];
	
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &m);
		
		map<string, string> R;
		
		for(int i = 0; i < n; i++) {
			scanf("%s", token);
			string acc(token);
			sort(token, token + strlen(token));
			R[token] = acc;
		}
		while(getchar() != '\n');
		printf("Case #%d:\n", ++cases);
		for(int i = 0; i < m; i++) {
			gets(lines);
			
			stringstream 	sin(lines);
			string			str, p;
			map<string, string>::iterator it;
			int 			f = 0;
						
			while(sin >> str) {
				p = str;
				sort(p.begin(), p.end());
				it = R.find(p);
				
				if(f)	putchar(' ');
				else	f = 1;
				
				if(it == R.end())
					printf("%s", str.c_str());
				else
					printf("%s", it->second.c_str());
			}
			puts("");
		}
	}
	return 0;
}
/*
2
9 2
andre copy exam free gimme lemme plox stuff yo
ardne lmeme cpoy yo eaxm polx
adnre gmime fere sfutf polx
4 1
abacabadabacaba abacaba aba a
a aba acbbaaa adccbbbbaaaaaaa
*/
