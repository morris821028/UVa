#include <stdio.h>
#include <string.h>
#include <set>
#include <iostream>
#include <vector>
using namespace std;

vector<int> putOrder[51][51]; // [m][i]
int main() {
	for (int m = 2; m < 50; m++) {
		for (int i = 0; i < m; i++) {
			int visited[50] = {}, pos = 0, skip = 0;
			putOrder[m][i].push_back(pos), visited[pos] = 1;
			for (int p = 1; p < m; p++) {
				skip = i % (m - p);
				while (skip >= 0) {
					pos++;
					if (pos >= m)	pos = 0;
					if (!visited[pos])
						skip--;
				}
				visited[pos] = 1;
				putOrder[m][i].push_back(pos);
			}
		}
	}
//	for (int i = 0; i < putOrder[15][6].size(); i++) // example
//		printf("%d\n", (putOrder[15][6][i] + 1)%15);
	char text[64];
	int cases = 0;
	while (gets(text)) {
		if (!strcmp("X", text))	break;
		int m = strlen(text);
		int appear[128] = {};
		for (int i = 0; text[i]; i++)
			appear[text[i]]++;
			
		int mxlen = 1, remainUsed[64];
		set<string> ret[64];
		for (int s = m-1; s >= 0; s--) {
			if (appear[text[s]] < 2) // must not start alphabet			
				continue;
			for (int n = m/2; n >= mxlen; n--) {
				if (ret[n].size() > 1)	continue;
				char plain[128];
				for (int i = 0; i < m; i++) {
					if (ret[n].size() > 1)	continue;
					int cnt[128] = {}, used[64] = {};
					int ok = 1;
					for (int p = 0; p < putOrder[m][i].size() && p < n; p++)
						plain[p] = text[(putOrder[m][i][p] + s)%m], used[(putOrder[m][i][p] + s)%m] = 1;
					plain[n] = '\0';
					for (int p = 0; p < n; p++) {
						cnt[plain[p]]++;
						if (cnt[plain[p]] * 2 > appear[plain[p]])
							ok = 0;
					}
					if (!ok)	continue;
					if (ret[n].find(plain) != ret[n].end())
						continue;
						
					int mm = 0;
					for (int p = 0; p < m; p++) {
						if (!used[p])
							remainUsed[mm++] = p;
					}
					for (int t = 0; t < mm; t++) {
						if (plain[0] != text[remainUsed[t]])	
							continue;
						if (ret[n].size() > 1)	continue;
						for (int j = i + 1; j < m; j++) {
							if (ret[n].size() > 1)	continue;
							int visited[50] = {};
							int pos = t, skip = 0, ok2 = 1;
							visited[pos] = 1;
							for (int p = 1; p < n; p++) {
								skip = j % (mm - p);
								while (skip >= 0) {
									pos++;
									if (pos >= mm)	pos = 0;
									if (!visited[pos])
										skip--;
								}
								if (plain[p] != text[remainUsed[pos]]) {
									ok2 = 0;
									break;
								}
								visited[pos] = 1;
							}
							if (ok2) {
								if (n > mxlen)
									mxlen = n;
								ret[n].insert(plain);
							}
						}
					}
				}
			}
		}
		printf("Code %d: ", ++cases);
		for (int i = m/2; i >= 0; i--) {
			if (ret[i].size()) {
				if (ret[i].size() == 1)
					printf("%s\n", ret[i].begin()->c_str());
				else
					puts("Codeword not unique");
				break;
			}
		}
	}
	return 0;
}
/*
APPURAAURGEGEWE
ABABABAB
THEACMPROGRAMMINGCONTEST
X
*/
