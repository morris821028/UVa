#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <omp.h>
using namespace std;
const int MAXN = 65536;
static char A[MAXN], B[MAXN];
#define DP_TYPE unsigned short
int lcs_len(const char *A, int na, const char *B, int nb, int dpf[]) {
//	DP_TYPE *dp[3];
//	for (int i = 0; i < 3; i++)
//		dp[i] = (DP_TYPE *) calloc(1, sizeof(DP_TYPE)*(nb+na+2));
	static DP_TYPE dp[3][MAXN<<1];
	if (na > 100 && nb > 10000) {
		for (int i = 0; i < 3; i++)
			memset(dp[i], 0, sizeof(DP_TYPE)*(nb+na+2));
		memset(dpf, 0, sizeof(DP_TYPE)*(nb+1));
		omp_set_num_threads(4);
		int last_l = 0, last_r = 0;
		for (int i = 0; i < na+nb-1; i++) {
			int l = max(0, i-na+1), r = min(i, nb-1);
			#pragma omp parallel for schedule(static) firstprivate(na, A, B)
			for (int j = l; j <= r; j++) {
				int x = i-j, y = j;
				if (A[x] == B[y])
					dp[2][j+1] = dp[0][j]+1;
				else
					dp[2][j+1] = dp[1][j] > dp[1][j+1] ? dp[1][j] : dp[1][j+1];
			}
			if (i-l == na-1)
				dpf[l+1] = dp[2][l+1];
			memcpy(dp[0]+last_l+1, dp[1]+last_l+1, sizeof(DP_TYPE)*(last_r-last_l+1));
			memcpy(dp[1]+l+1, dp[2]+l+1, sizeof(DP_TYPE)*(r-l+1));
			last_l = l, last_r = r;
		}
	} else {
		memset(dp[0], 0, sizeof(int)*(nb+1));
		dp[1][0] = 0;
		for (int i = 1; i <= na; i++) {
			for (int j = 1; j <= nb; j++) {
				if (A[i-1] == B[j-1])
					dp[1][j] = dp[0][j-1]+1;
				else
					dp[1][j] = max(dp[1][j-1], dp[0][j]);
			}
			memcpy(dp[0], dp[1], sizeof(DP_TYPE)*(nb+1));
		}
		for (int i = 0; i <= nb; i++)
			dpf[i] = dp[0][i];
	}
//	for (int i = 0; i < 3; i++)
//		free(dp[i]);
	return dpf[nb];
}

string find_lcs(string &a, string &b) {
	int na = a.length();
	int nb = b.length();

	if (na > nb)
		swap(a, b), swap(na, nb);

	if (na == 0)
		return "";

	if (na == 1) {
		for (int i = 0; i < nb; i++) {
			if (a[0] == b[i])
				return string(1, b[i]);
		}
		return "";
	}

	static int t1[MAXN];
	static int t2[MAXN];
	int len = lcs_len(a.c_str(), na, b.c_str(), nb, t1);
	if (len == 0)
		return "";
	int half_len = na / 2;
	string la = a.substr(0, half_len);
	string ra = a.substr(half_len);
	string tmp_b = b;
	lcs_len(la.c_str(), half_len, b.c_str(), nb, t1);
	reverse(ra.begin(), ra.end());
	reverse(tmp_b.begin(), tmp_b.end());
	lcs_len(ra.c_str(), na - half_len, tmp_b.c_str(), nb, t2);
	int split = -1;
	for (int i = 0; i <= nb; i++) {
		if (t1[i] + t2[nb-i] == len) {
			split = i;
			break;
		}
	}

	string lb = b.substr(0, split);
	string rb = b.substr(split);
	reverse(ra.begin(), ra.end());

	string sl = find_lcs(la, lb);
	string sr = find_lcs(ra, rb);

	return sl + sr;
}
int main() {
//	freopen("in.txt", "r", stdin);
	int dp[MAXN];
	while (scanf("%s %s", A, B) == 2) {
		string a = A, b = B;
		int len = lcs_len(a.c_str(), strlen(A), b.c_str(), strlen(B), dp);
		printf("%d\n", len);
		string v = find_lcs(a, b);
		printf("%s\n", v.c_str());
	}
	return 0;
}


