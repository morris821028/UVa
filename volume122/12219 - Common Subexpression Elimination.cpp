#include <bits/stdc++.h>
using namespace std;
static const int MAXV = 50005;
static char expr[524288];
typedef tuple<int, int, int> mkey_t;
struct key_hash : public std::unary_function<mkey_t, std::size_t> {
	std::size_t operator()(const mkey_t& k) const {
		return std::get<0>(k) ^ std::get<1>(k) ^ std::get<2>(k);
	}
};
struct key_equal : public std::binary_function<mkey_t, mkey_t, bool> {
	bool operator()(const mkey_t& v0, const mkey_t& v1) const {
		return  v0 == v1;
	}
};
unordered_map<tuple<int, int, int>, int, key_hash, key_equal> re;
char *ptr[MAXV];
pair<int, int> val[MAXV];
int stamp = 0;
int dfs1(int &idx) {
	stamp++;
	int fid = 0, lid = -1, rid = -1;
	int mid = stamp, off = idx+1;
	ptr[mid] = expr+idx;
	while (expr[idx] && isalpha(expr[idx]))
		fid = fid*27 + expr[idx]-'a'+1, idx++;

	if (expr[idx] == '(') {
		expr[idx] = '\0';
		idx++;
		lid = dfs1(idx);
		idx++;
		rid = dfs1(idx);
		idx++;
	} else {
		expr[idx] = '\0';
	}
	auto u = make_tuple(fid, lid, rid);
	val[mid] = make_pair(lid, rid);
	int &ret = re[u];
	if (ret == 0)
		ret = mid;
	else
		stamp--;
	return ret;
}
void dfs2(int mid) {
	if (ptr[mid]) {
		printf("%s", ptr[mid]);
		ptr[mid] = NULL;
	} else {
		printf("%d", mid);
		return ;
	}
	int lid = val[mid].first, rid = val[mid].second;
	if (lid == -1)
		return;
	putchar('(');
	dfs2(lid);
	putchar(',');
	dfs2(rid);
	putchar(')');
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", expr);
		re.clear();
		int idx = 0;
		stamp = 0;
		dfs1(idx);
		stamp = 0;
		dfs2(1);
		puts("");
	}
	return 0;
}
/*
3
this(is(a,tiny),tree)
a(b(f(a,a),b(f(a,a),f)),f(b(f(a,a),b(f(a,a),f)),f))
z(zz(zzzz(zz,z),zzzz(zz,z)),zzzz(zz(zzzz(zz,z),zzzz(zz,z)),z))
*/
