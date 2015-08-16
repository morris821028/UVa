#include <stdio.h> 
#include <string.h>
#include <vector>
using namespace std;
class GrayCode {
public:
	vector<int> v;
	static int overflow;
	GrayCode(vector<int> a) { 
		v = a;
	}
	GrayCode binary2gray(vector<int> x) const {
		vector<int> a = x, b = x;
		rshift(b);
		_xor(a, b);
    	return GrayCode(a);
	}
	GrayCode operator+(const unsigned long long &x) const {
		overflow = 0;
		vector<int> b = to_binary();
		for (int i = 0; i < 64; i++) {
			if ((x>>i)&1) {
				if (i >= b.size()) {
					overflow = 1;
					break;
				}
				b[i]++;
			}
		}
		int carry = 0;
		for (int i = 0; i < b.size(); i++) {
			b[i] += carry;
			carry = b[i] /2;
			b[i] %= 2;
		}
		if (carry)	overflow = 1;
		return binary2gray(b);
	}
	vector<int> to_binary() const {
		vector<int> a = v, mask = v;
	    for (rshift(mask); !zero(mask); rshift(mask))
	    	_xor(a, mask);
	    return a;
	}
	int zero(vector<int> &a) const {
		int r = 1;
		for (int i = 0; i < a.size() && r; i++)
			r &= a[i] == 0;
		return r;
	}
	void rshift(vector<int> &r) const {
		for (int i = 1; i < r.size(); i++)
			r[i-1] = r[i];
		r[r.size()-1] = 0;
	}
	void _xor(vector<int> &a, vector<int> &b) const {
		for (int i = 0; i < a.size(); i++)
			a[i] ^= b[i];
	}
	void println() {
		for (int i = 0; i < v.size(); i++)
			printf("%d ", v[i]);
		puts("");
	} 
};
int GrayCode::overflow = 0;
int main() {
	int testcase, n, x;
	unsigned long long nextK;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %llu", &n, &nextK);
		int zero[1024] = {}, mask[1024] = {}, goal[1024] = {};
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			mask[i] = x;
			goal[i] = 1^x;
		}
		int oflag = 0;
		vector<int> b = GrayCode(vector<int>(goal, goal+n)).to_binary();
		for (int i = n-1; i >= 0; i--) {
			int t = i < 64 ? (nextK>>i)&1 : 0;
			if (t != b[i]) {
				oflag = t > b[i];
				break;
			}
		}
		if (oflag) {
			printf("%d\n", n);
			continue;
		}
		GrayCode a(vector<int>(zero, zero+n));
		a = (a + nextK);
		if (GrayCode::overflow == 1) {
			printf("%d\n", n);
			continue;
		}
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret += (a.v[i]^mask[i]) == 1;
		printf("%d\n", ret);
	}
	return 0;
}
/*
6
3 1
1 0 0
3 2
1 0 0
3 3
1 0 0
3 4
1 0 0
3 5
1 0 0
10 9876543210987654321
0 1 0 1 0 1 0 1 0 1
*/
