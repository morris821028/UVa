#include <bits/stdc++.h> 
using namespace std;

static const int MAXN = 64;
int n, m;
pair<int, int> cmds[MAXN];
int valid(int init) {
	int sum = 0, cnt = init, has = 0;
	for (int i = 0; i < m; i++) {
		if (cmds[i].first == 0) {
			if (has && sum%cnt)
				return 0;
			cnt += cmds[i].second;
			sum = 0, has = 1;
		} else if (cmds[i].first == 1) {
			if (has && sum%cnt)
				return 0;
			cnt -= cmds[i].second;
			if (cnt <= 0)
				return 0;
			sum = 0, has = 1;
		} else {
			sum += cmds[i].second;
		}
	}
	return 1;
}
pair<int, int> bound() {
	int cnt = 0;
	int l = 1;
	int sum = 0, has = 0;
	for (int i = 0; i < m; i++) {
		if (cmds[i].first == 0) {
			cnt += cmds[i].second;
			has = 1;
		} else if (cmds[i].first == 1) {
			cnt -= cmds[i].second;
			if (cnt <= 0)
				l = max(l, -cnt + 1);
			has = 1;
		} else {
			sum += cmds[i].second;
		}
	}
	int r = 100000;
	return {l, r};
}
int main() {
	while (scanf("%d", &n) == 1 && n) {
		m = 0;
		for (int i = 0; i < n; i++) {
			char s[16];
			int v;
			scanf("%s %d", s, &v);
			if (s[0] == 'I')
				cmds[m++] = {0, v};
			else if (s[0] == 'O')
				cmds[m++] = {1, v};
			else if (s[0] == 'P')
				cmds[m++] = {2, v};
		}
		
		pair<int, int> b = bound();
		vector<int> ret;
		for (int i = b.first; i <= 100000; i++) {
			if (valid(i)) {
				ret.push_back(i);
				if (b.second == INT_MAX)
					break;
			}
		}

		if (ret.size() && (ret.back() == 100000)) {
			printf("SIZE >= %d\n", ret[0]);
		} else if (ret.size() == 0) {
			puts("IMPOSSIBLE");
		} else {
			for (int i = 0; i < ret.size(); i++) {
				printf("%d%c", ret[i], " \n"[i==ret.size()-1]);
			}
		}
		
	}
	return 0;
}
/*
5
IN 1
PAY 7
IN 1
PAY 7
IN 1

7
IN 1
COLLECT 20
PAY 30
PAY 12
IN 2
PAY 30
OUT 3

3
IN 1
PAY 8
OUT 3

1
OUT 5

3
IN 1
PAY 5 
IN 1

0
*/
