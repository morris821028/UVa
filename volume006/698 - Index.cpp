#include <bits/stdc++.h>
using namespace std;

int main() {
	char s[65536];
	int cases = 0;
	while (fgets(s, 65536, stdin)) {
		multiset<string> Q;
		while (s[0] != '\n') {
			for (int i = 0; s[i]; i++)
				s[i] = toupper(s[i]);
			s[strlen(s)-1] = '\0';
			Q.insert(s);
			fgets(s, 65536, stdin);
		}

		int lines = 0;
		map<string, set<int>> M;
		while (fgets(s, 65536, stdin)) {
			if (s[0] == '\n')
				break;
			lines++;
			for (int i = 0; s[i]; i++) {
				s[i] = toupper(s[i]);
				if (!isalnum(s[i]))
					s[i] = ' ';
			}
			stringstream sin(s);
			string token;
			while (sin >> token) {
				if (Q.find(token) != Q.end())
					M[token].insert(lines);
			}
		}

		printf("Case %d\n", ++cases);
		for (auto q : Q) {
			auto it = M.find(q);
			if (it == M.end())
				continue;
			printf("%s ", q.c_str());
			int st = -1, ed = -1, f = 0;
			for (auto v : it->second) {
				if (v == ed+1) {
					ed = v;
				} else {
					if (ed != -1) {
						if (f)
							printf(", ");
						f = 1;
						if (st == ed)
							printf("%d", st);
						else
							printf("%d-%d", st, ed);
					}
					st = v, ed = v;
				}
			}
			if (ed != -1) {
				if (f)
					printf(", ");
				f = 1;
				if (st == ed)
					printf("%d", st);
				else
					printf("%d-%d", st, ed);
			}
			puts("");
		}
		puts("");
	}
	return 0;
}

/*
empty
character
of
for
character
it

An empty line has no characters in it at all (except for
the end of line character). No word will have more than
ten characters in it. The end of the cases will be followed
by another empty line. It follows the empty line ending the
text of the last case.

Repeat
A
line

A repeat of a word on a line does not result in a repeat of the
line number in the index.


*/
