#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;
#define MAXN 65536
#define INF 0x3f3f3f3f
long long sum[MAXN], ssum[MAXN], isum[MAXN], issum[MAXN];
// binary indexed tree
int BIT[MAXN<<1];
int query(int x) {
	int ret = 0;
	while(x) {
		ret = max(ret, BIT[x]);
		x -= x&(-x);
	}
	return ret;
}
void modify(int x, int v, int L) {
	while(x <= L) {
		BIT[x] = max(BIT[x], v);
		x += x&(-x);
	}
}
int query2(int x) {
	int ret = INF;
	while(x) {
		ret = min(ret, BIT[x]);
		x -= x&(-x);
	}
	return ret;
}
void modify2(int x, int v, int L) {
	while(x <= L) {
		BIT[x] = min(BIT[x], v);
		x += x&(-x);
	}
}
int cases = 0, preA[MAXN], sufA[MAXN], start[MAXN], cover[MAXN<<1];
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout); 
	int testcase, n, A[MAXN];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &A[i]), start[i] = 0, cover[A[i] + MAXN] = -1;
		
		int L = 50000 + MAXN;
		for(int i = 0; i <= L; i++)
			BIT[i] = 0;
		for(int i = 1; i <= n; i++) {
			preA[i] = query(A[i] + MAXN);
			modify(A[i]+MAXN, i, L);
			if(preA[i] <= cover[A[i] + MAXN])
				start[i] = cover[A[i] + MAXN] + 1;
			cover[A[i] + MAXN] = i;
		}
		for(int i = 0; i <= L; i++)
			BIT[i] = n + 1;
		for(int i = n; i >= 1; i--) {
			sufA[i] = query2(A[i] + MAXN);
			modify2(A[i]+MAXN+1, i, L);
		}
		
		for(int i = 1; i <= n; i++)
			sum[i] = sum[i-1] + A[i];
		for(int i = 1; i <= n; i++)
			ssum[i] = ssum[i-1] + sum[i];
			
		isum[n+1] = issum[n+1] = 0;
		for(int i = n; i >= 1; i--)
			isum[i] = isum[i+1] + A[i];
		for(int i = n; i >= 1; i--)
			issum[i] = issum[i+1] + isum[i];
		
		long long ret = 0;
		for(int i = 1; i <= n; i++) {
			long long suma, a, sumb, b;
			if(start[i]) {
				suma = issum[start[i]] - issum[i], a = i - start[i];
				sumb = ssum[sufA[i]-1] - ssum[i], b = sufA[i] - i - 1;
				suma -= isum[i] * a;
				sumb -= sum[i] * b;
			} else {
				suma = issum[preA[i]+1] - issum[i], a = i - preA[i] - 1;
				sumb = ssum[sufA[i]-1] - ssum[i], b = sufA[i] - i - 1;
				suma -= isum[i] * a;
				sumb -= sum[i] * b;
			}
//			printf("index %d\n", i);
//			printf("%lld %lld\n", ssum[sufA[i]-1], ssum[i]);
//			printf("%lld %lld %lld %lld -- %lld\n", suma, a, sumb, b, (suma - A[i]*a*(a+1)/2) * (b + 1) + (sumb - A[i]*b*(b+1)/2) * (a + 1));
			ret += (suma - A[i]*a*(a+1)/2) * (b + 1) + (sumb - A[i]*b*(b+1)/2) * (a + 1);
//			long long test = 0;
//			for(int j = i; j >= 1; j--) {
//				if(A[j] < A[i])
//					break;
//				for(int k = i; k <= n; k++) {
//					if(A[k] < A[i])	break;
//					for(int l = j; l <= k; l++)
//						test += A[l] - A[i];
//				}
//			}
//			printf("DEBUG %lld\n", test);
		}
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
1
5
1 2 3 4 5

10
10
-7 2 -6 7 -9 5 -5 -3 9 3 
10
1 -7 9 2 4 7 -10 8 0 0 
10
-8 9 4 -8 1 2 -3 2 8 8 
10
-3 -4 0 -2 5 9 -3 -4 2 1 
10
3 -8 -9 -4 8 -9 -7 6 -10 -9 
10
-7 0 -2 8 -6 6 9 -5 -1 -3 
10
1 -10 7 -1 7 -10 5 -1 -10 9 
10
-2 9 -8 8 -7 0 -1 -8 7 -9 
10
-9 2 3 -8 -10 9 7 9 1 3 
10
3 5 1 -4 -6 -3 0 2 -5 -5 
*/
