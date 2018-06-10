#include <bits/stdc++.h>
using namespace std;

const int MAXN = 4096;
char s[16777216], *sptr;
char *shead[MAXN];
int slen[MAXN];
int C[MAXN];
void init() {
	sptr = s;
	memset(C, 0, sizeof(C));
}
char* read_str() {
	char *ret = sptr;
	scanf("%s", sptr);
	while (*sptr)	sptr++;
	sptr++;
	return ret;
}

int evolution(int from, int to) {
	char *a = shead[from];
	char *b = shead[to];
	for (; *a && *b; b++) {
		if (*a == *b)
			a++;
	}
	return *a == '\0';
}

void radix_sort(int n, int m) {
	static char *tmp[MAXN];
	static int tlen[MAXN];
	for (int i = 0; i <= n; i++)
		C[slen[i]]++;
	for (int i = m-1; i >= 0; i--)
		C[i] += C[i+1];
	for (int i = 0; i <= n; i++) {
		int pos = --C[slen[i]];
		tmp[pos] = shead[i];
		tlen[pos] = slen[i];
	}
	for (int i = 0; i <= n; i++)
		shead[i] = tmp[i], tlen[i] = slen[i];
}
int main() {
	int n, m;
	while (scanf("%d", &n) == 1) {
		init();
		shead[0] = read_str();
		for (int i = 1; i <= n; i++)
			shead[i] = read_str();
		for (int i = 0; i <= n; i++)
			slen[i] = strlen(shead[i]);

		m = slen[0];		
		radix_sort(n, m);

		pair<int, int> Q[2];
		static int prev[MAXN];
		int possible = 1;
		int split = 0;
		int Qn = 0;
		Q[0] = {0, 0}, Qn = 1;
		memset(prev, 0, sizeof(prev));
		for (int i = 1; i <= n; i++) {
//			printf("%d, %d %d, %d %d\n", Qn, Q[0].first, Q[0].second, Q[1].first, Q[1].second);
			if (Qn == 1) {
				int l = Q[0].first, r = Q[0].second;
				int tl = evolution(i, l);
				int tr = evolution(i, r);
				if (tl && tr) {
					Qn = 2;
					Q[0] = {i, l}, Q[1] = {i, r};
					split = i;
				} else if (tl) {
					if (l)
						prev[i] = l;
					Qn = 1;
					Q[0] = {i, r};
				} else if (tr) {
					if (r)
						prev[i] = r;
					Qn = 1;
					Q[0] = {i, l};
				} else {
					possible = 0;
					break;
				}
			} else {
				int m = Q[0].first;
				int l = Q[0].second, r = Q[1].second;
				if (evolution(i, m)) {
					if (m)
						prev[i] = m;
					Qn = 2;
					Q[0] = {i, l}, Q[1] = {i, r};
				} else if (evolution(i, l)) {
					if (l)
						prev[i] = l;
					if (r)
						prev[split] = r;
					Qn = 1;
					Q[0] = {i, m};
				} else if (evolution(i, r)) {
					if (l)
						prev[i] = r;
					if (r)
						prev[split] = l;
					Qn = 1;
					Q[0] = {i, m};
				} else {
					possible = 0;
					break;
				}
			}
		}
		
		if (!possible) {
			puts("impossible");
		} else {
			vector<int> L, R;
			int l, r;
			if (Qn == 2) {
				if (Q[1].second)
					prev[split] = Q[1].second;
			}
			l = Q[0].first, r = Q[0].second;
			while (l) {
				L.push_back(l);
				l = prev[l];
			}
			while (r) {
				R.push_back(r);
				r = prev[r];
			}
			printf("%d %d\n", L.size(), R.size());
			for (auto l : L)
				puts(shead[l]);
			for (auto r : R)
				puts(shead[r]);
		}
	}
	return 0;
}
/*
5
AACCMMAA
ACA
MM
ACMAA
AA
A
3
ACMA
ACM
ACA
AMA
1
AM
MA
4
AAAAAA
AA
AAA
A
AAAAA
*/
