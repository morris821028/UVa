#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class HASH {
public:
#define HSIZE 1572869
#define HNODE (2097152 + 10)
	struct Node {
		long long first;
		int second;
		Node(long long a = 0, int b = 0):
			first(a), second(b) {}
	};
	int head[HSIZE], next[HNODE], size;
	Node nodes[HNODE];
	
	unsigned long hash(unsigned long long x) {
		return (x * 2654435761LU)% HSIZE;
	}
	void init() {
		memset(head, -1, sizeof(head));
		size = 0;
	}
	Node& add(int hidx, Node s) {
		nodes[size] = s;
		next[size] = head[hidx];
		head[hidx] = size;
		size++;
		return nodes[size-1];
	}
	int& operator[](long long x) {
		static int i, hidx;
		hidx = hash(x);
		for (i = head[hidx]; i != -1; i = next[i]) {
			if (nodes[i].first == x)
				return nodes[i].second;
		}
		return add(hidx, Node(x, 0)).second;
	}
};

const int MAXS = 610000;
struct SuffixArray {
    int sa[MAXS], h[MAXS], n;
    int w[MAXS], ta[MAXS], tb[MAXS];
    char str[MAXS];
    void sort(int *x, int *y, int m) {
        static int i;
        for (i = 0; i < m; i++)
            w[i] = 0;
        for (i = 0; i < n; i++)
            w[x[y[i]]]++;
        for (i = 1; i < m; i++)
            w[i] += w[i-1];
        for (i = n-1; i >= 0; i--)
            sa[--w[x[y[i]]]] = y[i];
    }
    bool cmp(int *r, int a, int b, int l) {
        if (r[a] == r[b]) {
            if (a+l >= n || b+l >= n)
                return false;
            return r[a+l] == r[b+l];
        }
        return false;
    }
    void build_h() {
        int i, j, k;
        for (i = 0; i < n; i++)  ta[sa[i]] = i;
        for (i = 0; i < n; i++) {
            if (ta[i] == 0) {
                h[ta[i]] = 0;
                continue;
            }
            if (i == 0 || h[ta[i-1]] <= 1)
                k = 0;
            else
                k = h[ta[i-1]]-1;
            while (str[sa[ta[i]-1]+k] == str[sa[ta[i]]+k])
                k++;
            h[ta[i]] = k;
        }
    }
    void build() {// x: rank, y: second key
        int i, k, m = 128, p;
        int *x = ta, *y = tb, *z;
        n = strlen(str);
        x[n] = 0;
        for (i = 0; i < n; i++)
            x[i] = str[i], y[i] = i;
        sort(x, y, m);
        for (k = 1, p = 1; p < n; k *= 2, m = p) {
            for (p = 0, i = n-k; i < n; i++)
                y[p++] = i;
            for (i = 0; i < n; i++) {
                if (sa[i] >= k) {
                    y[p++] = sa[i]-k;
                }
            }
            sort(x, y, m);
            z = x, x = y, y = z;
            for (i = 1, p = 1, x[sa[0]] = 0; i < n; i++)
                x[sa[i]] = cmp(y, sa[i-1], sa[i], k) ? p-1 : p++;
        }
    }
    void debug() {
//    	printf("master %s\n", str);
    	
    	for (int i = 0; i < n; i++)
    		printf("%d\n", h[i]);
//    	for (int i = 0; i < n; i++) {
//			printf("%s %d\n", str + sa[i], h[i]);
//		}
    }
} sa;

char s[32767];
int sid[MAXS], slen[64];
HASH search_result;
void DC_search(int l, int r, int split) {
	if (l > r)	return;
	for (int i = l; i < r; i++) {
		if (sa.h[i] <= split)
			continue;
		
		int pl = i, pr;
		int lower = 0x3f3f3f3f; // find split
		long long mask = 0;
		while (i < r && sa.h[i] > split) {
			lower = min(lower, sa.h[i]);
			if (sid[sa.sa[i-1]] >= 0)
				mask |= 1LL<<sid[sa.sa[i-1]];
			i++;
		}
		
		if (sid[sa.sa[i-1]] >= 0)
			mask |= 1LL<<sid[sa.sa[i-1]];
		if (mask) 
			search_result[mask] = 0;
		pr = i;
		DC_search(pl, pr, lower);
	}
}
void single_search(int n) {
	long long cant = 0;
	for (int i = 1; i < sa.n; i++) {
		if (sa.h[i] > 0) {
			if (sid[sa.sa[i]] != -1 && sa.h[i] == slen[sid[sa.sa[i]]])
				cant |= 1LL<<sid[sa.sa[i]]; 	// S in S$, S$ < S
			if (sid[sa.sa[i-1]] != -1 && sa.h[i] == slen[sid[sa.sa[i-1]]])
				cant |= 1LL<<sid[sa.sa[i-1]]; 	// S in S#, S < S#
		}
	}
	for (int i = 0; i < n; i++)
		if (!((cant>>i)&1))
			search_result[1LL<<i] = 0;
}
int main() {
	int n, m;
	while (scanf("%d", &n) == 1 && n) {
		m = 0;
		
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			
			slen[i] = strlen(s);
			for (int j = 0; s[j]; j++, m++)
				sa.str[m] = s[j], sid[m] = i;
			sa.str[m] = 30 + i, sid[m] = -1, m++;
		}
		sa.str[m] = '\0';
		
		sa.build();
		sa.build_h();
//		sa.debug();
		
		search_result.init();
		
		DC_search(0, sa.n, 0);
		single_search(n);
		long long ret = search_result.size;
		printf("%lld\n", ret);

	}
	return 0;
}
/*
6
form
formal
malformed
for
man
remake
3
cool
cool
old
3
a
b
c

40
cbaccba
aeeaead
d
dceaea
e
becd
dedb
c
c
ddcae
ba
dcdb
db
aede
eccb
dda
eced
aaacd
c
dddbbdbb
bb
dcda
dedbb
deaea
ebbd
eeeaab
ebabae
dcdaabde
eaea
dac
bbaadad
ecde
cebc
cc
bdcd
c
cdacd
aaedbb
bcb
eaabcabb


*/
