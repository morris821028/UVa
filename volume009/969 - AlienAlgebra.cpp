#include <bits/stdc++.h> 
using namespace std;

int mhash_t(int e1, int e2) {
	return e1*13 + e2;
}

int mhash(char *s, int &idx) {
	char c = s[idx]; idx++;
	int ret = 0;
	if (c == 't') {
		idx++;
		int e1 = mhash(s, idx);
		idx++;
		int e2 = mhash(s, idx);
		idx++;
		ret = mhash_t(e1, e2);
	} else if (c == 'i') {
		idx++;
		ret = mhash(s, idx);
		idx++;
	} else if (c == 'k') {
		idx++;
		int x = mhash(s, idx);
		idx++;
		int y = mhash(s, idx);
		idx++;
		ret = mhash_t(y, mhash_t(x, 1));
	} else if (c == '0') {
		ret = 1;
	} else {
		assert(false);
	}
	return ret;
}
int main() {
	int testcase;
	char s1[65536], s2[65536];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s %s", s1, s2);
		int i = 0, j = 0;	
		int h1 = mhash(s1, i);
		int h2 = mhash(s2, j);
		if (h1 == h2)
			puts("true");
		else
			puts("false");
	}
	return 0;
}
/*
2
t(0,t(t(0,0),0))
i(i(k(t(0,0),i(0))))
i(t(0,t(0,0)))
k(0,t(0,0))
*/
