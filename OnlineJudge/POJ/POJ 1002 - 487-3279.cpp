#include <bits/stdc++.h>
using namespace std;

int main() {
	char mm[128];
	mm['A'] = mm['B'] = mm['C'] = 2;
	mm['D'] = mm['E'] = mm['F'] = 3;
	mm['G'] = mm['H'] = mm['I'] = 4;
	mm['J'] = mm['K'] = mm['L'] = 5;
	mm['M'] = mm['N'] = mm['O'] = 6;
	mm['P'] = mm['R'] = mm['S'] = 7;
	mm['T'] = mm['U'] = mm['V'] = 8;
	mm['W'] = mm['X'] = mm['Y'] = 9;
	int n;
	while (scanf("%d", &n) == 1) {
		map<string, int> R;
		char s[128], vs[128];
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			int m = 0;
			for (int j = 0; s[j]; j++) {
				if (isdigit(s[j]))
					vs[m++] = s[j];
				if (isupper(s[j]))
					vs[m++] = mm[s[j]] + '0';
				if (m == 3)
					vs[m++] = '-';
			}
			vs[m] = '\0';
			R[vs]++;
		}
		
		int has = 0;
		for (auto &x : R) {
			if (x.second > 1)
				printf("%s %d\n", x.first.c_str(), x.second), has = 1;
		}
		if (!has)
			puts("No duplicates.");
	}
	return 0;
}
