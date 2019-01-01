#include <bits/stdc++.h>
using namespace std;

struct Record {
	vector<int> tuple;
	set<int> s;
	int c, w;
	Record() {
		s.clear();
		tuple.clear();
	}
};
int m;
vector<int> S;
vector<Record> R;

int satisfy(Record &r, vector<int> t) {
	int c = 0, w = 0;
	for (int i = 0; i < t.size(); i++)
		c += t[i] == r.tuple[i];
	if (c != r.c)
		return 0;
	for (int i = 0; i < t.size(); i++)
		w += r.s.find(t[i]) != r.s.end();
	w -= c;
	return w == r.w;
}

int rough_satisfy(vector<int> t) {
	for (int i = 0; i < R.size(); i++) {
		Record &r = R[i];
		int w = 0;
		for (int i = 0; i < t.size(); i++)
			w += r.s.find(t[i]) != r.s.end();
		if (w != r.w + r.c)
			return 0;
	}
	return 1;
}

void guess() {
	int sel[20] = {};
	int n = S.size();
	for (int i = n-m; i < n; i++)
		sel[i] = 1;
	sort(S.begin(), S.end());
	vector<int> ret;
	do {
		vector<int> T;
		for (int i = 0; i < n; i++) {
			if (sel[i])
				T.push_back(S[i]);
		}

		if (rough_satisfy(T)) {
			do {
				int valid = 1;
				for (int i = 0; i < R.size(); i++) {
					if (!satisfy(R[i], T)) {
						valid = 0;
						break;
					}
				}
				if (valid) {
					if (ret.size()) {
						puts("N");
						return;
					}
					ret = T;
				}
			} while (next_permutation(T.begin(), T.end()));
		} 
	} while (next_permutation(sel, sel+n));

	if (ret.size() == 0) {
		puts("N");
		return ;
	}
	printf("(");
	for (int i = 0; i < m; i++) {
		printf("%c%c", ret[i], ",)"[i==m-1]);
	}
	puts("");
}

int main() {
	char s[1024];
	while (fgets(s, 1024, stdin)) {
		stringstream sin(s);
		R.clear(), S.clear();
		string x;
		while (sin >> x)
			S.push_back(x[0]);
		fgets(s, 1024, stdin);
		sscanf(s, "%d", &m);
		while (fgets(s, 1024, stdin)) {
			if (s[0] == '%')
				break;
			char item[1024];
			int c, w;
			sscanf(s, "%s %*s (%d,%d)", item, &c, &w);
			for (int i = 0; item[i]; i++) {
				if (item[i] == '(' || item[i] == ',' || item[i] == ')')
					item[i] = ' ';
			}
			Record r;
			stringstream sin(item);
			while (sin >> x)
				r.tuple.push_back(x[0]), r.s.insert(x[0]);
			assert(r.tuple.size() == m);
			r.c = c, r.w = w;
			R.push_back(r);
		}

		guess();
	}
	return 0;
}
/*
1 2 3 4 5 6 7 8 9
3
(1,1,1) -> (0,0)
(2,2,2) -> (0,0)
(3,3,3) -> (0,0)
(4,4,4) -> (1,0)
(5,5,5) -> (0,0)
(6,6,6) -> (0,0)
(7,7,7) -> (1,0)
(8,8,8) -> (1,0)
(4,7,8) -> (1,2)
(4,8,7) -> (0,3)
(8,7,4) -> (0,3)
(7,8,4) -> (1,2)
(8,4,7) -> (1,2)
%
1 2 3 4 5 6 7 8 9
3
(1,1,1) -> (0,0)
(2,2,2) -> (0,0)
(3,3,3) -> (0,0)
(4,4,4) -> (1,0)
(5,5,5) -> (0,0)
(6,6,6) -> (0,0)
(7,7,7) -> (1,0)
(8,8,8) -> (1,0)
(9,9,9) -> (0,0)
%
*/
