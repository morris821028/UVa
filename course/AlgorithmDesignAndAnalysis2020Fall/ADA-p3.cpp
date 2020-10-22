#include <bits/stdc++.h>
using namespace std;

// Algorithm Design and Analysis (NTU CSIE, Fall 2020)
// Problem 3. ADA Party

const int MAXN = 500005;
const int32_t MIN = LONG_MIN;
const int32_t MAX = LONG_MAX;
int32_t a[MAXN];
int32_t lsum[MAXN], rsum[MAXN];
int32_t lmin[MAXN], lmax[MAXN];
int32_t rmin[MAXN], rmax[MAXN];

int cases = 0;
int mark[MAXN];
int counter[MAXN];
int n, k;
void inc(int32_t val) {
	val = (val%k+k)%k;
	if (mark[val] != cases)
		mark[val] = cases, counter[val] = 0;
	counter[val]++;
}
void dec(int32_t val) {
	val = (val%k+k)%k;
	if (mark[val] != cases)
		mark[val] = cases, counter[val] = 0;
	counter[val]--;
}
int get(int32_t val) {
	val = (val%k+k)%k;
	if (mark[val] != cases)
		mark[val] = cases, counter[val] = 0;
	return counter[val];
}
int64_t common(int l, int m, int r) {
	int64_t ret = 0;
	cases++;  // max and min is same on both end
	for (int i = m, j = m+1, jl = m+1; i >= l; i--) {
		while (j <= r && (rmax[j] <= lmax[i] && rmin[j] >= lmin[i])) {
			inc(rsum[j]-rmin[j]);
			j++;
		}
		while (jl < j && (rmin[jl] > lmin[i] || rmax[jl] < lmax[i])) {
			dec(rsum[jl]-rmin[jl]);
			jl++;
		}
		if (j > m+1 && lmin[i] == rmin[j-1] && lmax[i] == rmax[j-1])
			ret += get(k-(lsum[i]-lmax[i]));
	}
	return ret;
}
int64_t divide(int l, int r) {
	if (l >= r)
		return 0;
	int m = (l+r)/2;
	int32_t sum = 0;
	int32_t mn = MAX, mx = MIN;

	for (int i = m; i >= l; i--) {
		sum += a[i], mn = min(mn, a[i]), mx = max(mx, a[i]);
		if (sum >= k)	sum %= k;
		lsum[i] = sum, lmin[i] = mn, lmax[i] = mx;
	}
	sum = 0, mn = MAX, mx = MIN;
	for (int i = m+1; i <= r; i++) {
		sum += a[i], mn = min(mn, a[i]), mx = max(mx, a[i]);
		if (sum >= k)	sum %= k;
		rsum[i] = sum, rmin[i] = mn, rmax[i] = mx;
	}

	int64_t c1 = 0, c2 = 0, c3 = 0, c4 = 0;

	cases++; // min max on the left
	for (int i = m, j = m+1; i >= l; i--) {
		while (j <= r && lmin[i] < a[j] && a[j] < lmax[i]) {
			inc(rsum[j]);
			j++;
		}
		if (i < m)
			c1 += get(k-(lsum[i]-lmin[i]-lmax[i]));
	}
	cases++; // min max on the right
	for (int i = m+1, j = m; i <= r; i++) {
		while (j >= l && rmin[i] < a[j] && a[j] < rmax[i]) {
			inc(lsum[j]);
			j--;
		}
		if (i > m+1)
			c2 += get(k-(rsum[i]-rmin[i]-rmax[i]));
	} 

	cases++;  // min on the left, max on the right
	for (int i = m, j = m+1, jl = m+1; i >= l; i--) {
		while (j <= r && rmin[j] >= lmin[i]) {
			inc(rsum[j]-rmax[j]);
			j++;
		}
		while (jl < j && rmax[jl] < lmax[i]) {
			dec(rsum[jl]-rmax[jl]);
			jl++;
		}
		c3 += get(k-(lsum[i]-lmin[i]));
	}
	cases++; // min on the right, max on the left
	for (int i = m+1, j = m, jl = m; i <= r; i++) {
		while (j >= l && lmin[j] >= rmin[i]) {
			inc(lsum[j]-lmax[j]);
			j--;
		}
		while (jl > j && lmax[jl] < rmax[i]) {
			dec(lsum[jl]-lmax[jl]);
			jl--;
		}
		c4 += get(k-(rsum[i]-rmin[i]));
	}
	int64_t local = c1 + c2 + c3 + c4 - common(l, m, r);
	return local + divide(l, m) + divide(m+1, r);
}

int main() {
	while (scanf("%d %d", &n, &k) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		memset(counter, 0, sizeof(counter[0])*k);
		int64_t ret = divide(0, n-1);
		printf("%lld\n", ret);
	}
	return 0;
}
/*
   5 3
   5 6 1 8 4
   ==> 6

   10 2
   6 9 3 4 5 6 1 7 8 3
   ==> 25

   25 7
   20 25 6 1 15 7 16 13 14 24 11 19 18 5 21 3 23 8 4 9 12 10 22 2 17
   ==> 72
 */
