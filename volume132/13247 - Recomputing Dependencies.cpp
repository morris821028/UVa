#include <bits/stdc++.h>
using namespace std;
const int MAXS = 16777216;
const int MAXN = 262144;
char line[MAXS];
int mprev[MAXN];
int main() {
	while (fgets(line, MAXS, stdin) && line[0] != '0') {
		int a_pos = 0, b_pos = 0;
		line[strlen(line)-1] = '\0';
		mprev[0] = 0;
		for (int i = 0; line[i]; ) {
			while (line[i] == ' ')
				i++;
			if (a_pos)
				putchar(' ');
			a_pos++;
			if (line[i] == '-') {
				b_pos++;
				mprev[b_pos] = mprev[b_pos-1]+1;
				putchar('-');
				i++;
			} else if (line[i] == '#') {
				mprev[b_pos]++;
				putchar('#');
				i++;
			} else if (line[i] >= '0') {
				b_pos++;
				mprev[b_pos] = mprev[b_pos-1]+1;
				int x = 0;
				while (line[i] >= '0' && line[i] <= '9')
					x = x*10 + line[i]-'0', i++;
				assert(b_pos-x-1 >= 0);
				int pos = a_pos - mprev[b_pos-x-1]-1;
				assert(pos > 0);
				printf("%d", pos);
			}
		}
		puts("");
	}
	return 0;
}
/*
- - # # - # - 3 2 -
- - # #  - # - # 3 2 -
- - # #  - # - # 3 # 2 - 
- - # #  - # - # 3 # 2 - - 7
# - - # # - # - 3 2 -
# - - # #  - # - # 3 2 -
# # - - # #  - # - # 3 # 2 - 
# - - # #  - # - # 3 # 2 - - 7
- - # #  - # - # 3 # 2 - - 7
0
*/
