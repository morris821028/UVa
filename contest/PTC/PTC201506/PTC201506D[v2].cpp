#include <stdio.h>
#include <list>
#include <algorithm>
using namespace std;

struct Interval {
	int l, r, inv;
	Interval(int a = 0, int b = 0, int c = 0):
		l(a), r(b), inv(c) {}
};

list<Interval>::iterator split(list<Interval> &A, int x) {
	list<Interval>::iterator it = A.begin(), jt;
	for (int l = 1, r = 0; it != A.end(); l = r+1, it++) {
		r = l + it->r - it->l;	// index [l, r]
		if (l <= x && x <= r) {
			if (it->inv == 0) {
				int mid = it->l + (x - l);
				jt = A.insert(it, Interval(it->l, mid, 0));
				if (x < r)
					A.insert(it, Interval(mid+1, it->r, 0));
				A.erase(it);
			} else {
				int mid = it->r - (x - l);
				jt = A.insert(it, Interval(mid, it->r, 1));
				if (x < r)
					A.insert(it, Interval(it->l, mid-1, 1));
				A.erase(it);
			}
			return jt;
		}
	}
	return A.end();
}
int main() {
	int testcase;
    int N, Q;
    int a, b;
    scanf("%d", &testcase);
    while (testcase--) {
    	scanf("%d %d", &N, &Q);
        
		list<Interval> A;
		A.push_back(Interval(1, N, 0));
		
		for (int i = 1; i <= Q; i++) {
			scanf("%d %d", &a, &b);
			list<Interval>::iterator at, bt, ct;
			list<Interval> tmp;
			
			ct = at = split(A, a-1), bt = split(A, b);
			at++, bt++;
			tmp.splice(tmp.begin(), A, at, bt);
			ct++;
						
			tmp.reverse();
			for (list<Interval>::iterator it = tmp.begin(); it != tmp.end(); it++)
				it->inv = !it->inv; 
			A.splice(ct, tmp);

		}			
		
		int sz = 0;
		long long ret = 0;
		for (list<Interval>::iterator it = A.begin(); it != A.end(); it++) {
			long long l = it->l, r = it->r;
			long long sum = (long long)(l+r)*(r-l+1)/2;
			long long a, b;

			if (it->inv)	swap(l, r);
			long long an = l < r ? ((r-l)/2+1) : ((l-r)/2+1), d = l < r ? 2 : -2;
			a = (2*l + (an-1)*d)*(an)/2;
			b = sum - a;
			ret += sz%2 ? b : a;	
			sz += it->r - it->l + 1;
		}
		printf("%lld\n", ret);
    }
    return 0;
}
