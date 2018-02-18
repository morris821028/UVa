#include <bits/stdc++.h>
using namespace std;
struct Stat {
	int cnt;
	string mn, mx;
	Stat() {
		cnt = 0, mn = mx = "";
	}
};
const int MAXS = 32;
string inv_scramble(const char s[]) {
	static char buf[MAXS];
	int len = strlen(s);
	buf[0] = s[0], buf[len] = '\0';
	buf[len-1] = s[len-1];
	for (int i = 1; i < len-1; i++)
		buf[i] = s[i];
	sort(buf+1, buf+len-1);
	return string(buf);
}
int main() {
	char s[MAXS];
	int n, q;
	unordered_map<string, Stat> R;
	while (scanf("%d", &n) == 1) {
		R.clear();
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			string t = inv_scramble(s);
			Stat &c = R[t];
			c.cnt++;
			if (c.cnt == 1) {
				c.mn = c.mx = s;
			} else {
				c.mn = min(c.mn, string(s));
				c.mx = max(c.mx, string(s));
			}
		}
		
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%s", s);
			string t = inv_scramble(s);
			Stat &c = R[t];
			printf("%d", c.cnt);
			if (c.cnt == 0)
				puts("");
			else
				printf(" %s %s\n", c.mn.c_str(), c.mx.c_str());
		}
	}
	return 0;
}

/*
5
aabab
aaaab
aaabb
aaaaa
xyxyx
5
aaaaa
aabab
zzzzz
kkkkk
aaabb
*/
