#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	vector<long long> V;
	vector<long long> T;
	int ql, qr;
	int merge(int l, int mid, int r) {
		int idx1 = l, idx2 = mid+1;
		int top = 0;
		int ret = 0;
		
		// Solution 1
//		for (int i = mid+1; i <= r; i++) {
//			int a, b;
//			a = upper_bound(V.begin()+l, V.begin()+mid+1, V[i] - ql) - V.begin();
//			b = lower_bound(V.begin()+l, V.begin()+mid+1, V[i] - qr) - V.begin();
//			ret += a - b;
//		}
		
		// Solution 2-1
//		int tl = mid+1, tr = mid+1;
//		for (int i = l; i <= mid; i++) {
//			while (tl <= r && V[tl] - V[i] < ql)
//				tl++;
//			while (tr <= r && V[tr] - V[i] <= qr)
//				tr++;
//			ret += tr - tl;
//		}
		
		// Solution 2-2
		int tl = l, tr = l;
		for (int i = mid+1; i <= r; i++) {
			while (tl <= mid && V[i] - V[tl] > qr)
				tl++;
			while (tr <= mid && V[i] - V[tr] >= ql)
				tr++;
			ret += tr - tl;
		}
		
		while (idx1 <= mid && idx2 <= r) {
			if (V[idx1] < V[idx2]) {
				T[top++] = V[idx1], idx1++;
			} else {
				T[top++] = V[idx2], idx2++;
			}
		}
		
		while (idx1 <= mid)
			T[top++] = V[idx1], idx1++;
		while (idx2 <= r)
			T[top++] = V[idx2], idx2++;
			
		for (int i = l, j = 0; i <= r; i++, j++)
			V[i] = T[j];
		return ret;
	}
	int DC(int l, int r) {
		if (l >= r)	return 0;
		int mid = (l + r) /2;
		int ret = DC(l, mid);
		ret += DC(mid+1, r);
		return ret + merge(l, mid, r);
	}
    int countRangeSum(vector<int>& A, int lower, int upper) {
    	int n = A.size();
    	long long sum = 0, base = 0;
    	V.resize(n+1), T.resize(n+1);
    	V[0] = 0;
    	for (int i = 0; i < n; i++)
    		sum += A[i], V[i+1] = sum;
    	ql = lower, qr = upper;
    	return DC(0, n);
    }
};

Solution t;
void test1() {
	int A[] = {0, 0};
	vector<int> vA(A, A+2);
	int ret = t.countRangeSum(vA, 0, 0);
	printf("%d\n", ret);
}
void test2() {
	int A[] = {-2, 5, -1};
	vector<int> vA(A, A+3);
	int ret = t.countRangeSum(vA, -2, 2);
	printf("%d\n", ret);
}
void test3() {
	int A[] = {1, 1, 1, 1};
	vector<int> vA(A, A+4);
	int ret = t.countRangeSum(vA, 0, 4);
	printf("%d\n", ret);
}
int test4() {
	int A[] = {0,-3,-3,1,1,2};
	vector<int> vA(A, A+6);
	int ret = t.countRangeSum(vA, 3, 5);
	printf("%d\n", ret);
}
int main() {
	test4();
	test1();
	test2();
	test3();
	return 0;
}

