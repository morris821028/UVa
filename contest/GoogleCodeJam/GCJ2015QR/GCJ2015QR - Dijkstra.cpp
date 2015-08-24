#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXL = 32767;
char s[MAXL];
int table[5][5] = {
		{},
	// 	   1, 2, 3, 4
	// 1  
		{0, 1, 2, 3, 4},
	// 2
		{0, 2, -1, 4, -3},
	// 3
		{0, 3, -4, -1, 2},
	// 4
		{0, 4, 3, -2, -1}
};

int prefix[MAXL], suffix[MAXL], all[MAXL];
int L, X;
int preSt[MAXL][8], sufSt[MAXL][8];
int add(int a, int b) { // a * b
	int sign1 = a > 0 ? 1 : -1;
	int sign2 = b > 0 ? 1 : -1;
	int tmp;
	tmp = table[abs(a)][abs(b)];
	a = tmp * sign1 * sign2;
	return a;
}

int tree[MAXL];
void build(int k, int l, int r) {
	if (l == r) {
		tree[k] = s[l];
		return ;
	}
	int mid = (l + r)/2;
	build(k<<1, l, mid);
	build(k<<1|1, mid+1, r);
	tree[k] = add(tree[k<<1], tree[k<<1|1]);
}
int query(int k, int l, int r, int x, int y) {
	if (x <= l && r <= y)
		return tree[k];
	int mid = (l + r)/2;
	if (y <= mid)
		return query(k<<1, l, mid, x, y);
	else if (x > mid)
		return query(k<<1|1, mid+1, r, x, y);
	else
		return add(query(k<<1, l, mid, x, y), query(k<<1|1, mid+1, r, x, y));
}
int solve(int cycle) {
	int ok = 0;
		for (int i = 0; i < L; i++) {
			for (int j = 0; j <= cycle; j++) {
				if (preSt[i][j] == 2) { // reduce i
					for (int p = 0; p < L; p++) {
						for (int q = 0; q <= cycle; q++) {
							if (sufSt[p][q] == 4) { // reduce k
								int val1 = 0, val2 = 0, val, x;
								if (i != L-1)	val1 = suffix[i+1];
								else			val1 = 1;
								if (p != 0)		val2 = prefix[p-1];
								else			val2 = 1;
								for (int k = 0; k <= cycle; k++) {
									if (k == 0) {
										if (i < p - 1) {
											val = query(1, 0, L-1, i+1, p-1);
											x = j + q + 1;
										} else {
											continue;
										}
									} else {
										val = add(add(val1, all[k]), val2);
										x = j + q + 2 + k;
									}
									
									if (val == 3 && x <= X && (X - x)%cycle == 0) { // reduce j
										ok = 1;
										return 1;
									}
								}
							}
						}
					}
				}
			}
		}
		return 0;
}
int main() {
	// printf("%d\n", add(add(3, 2), 3)); // j i j = i
	int testcase, cases = 0;

	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &L, &X);
		scanf("%s", s);
		for (int i = 0; i < L; i++) {
			if (s[i] == 'i')		s[i] = 2;
			else if (s[i] == 'j')	s[i] = 3;
			else if (s[i] == 'k')	s[i] = 4;
		}
		build(1, 0, L-1);
		
		for (int i = 0, val = 1; i < L; i++) {
			val = add(val, s[i]);
			prefix[i] = val;
		}
		
		for (int i = L - 1, val = 1; i >= 0; i--) {
			val = add(s[i], val);
			suffix[i] = val;
		}
		
		int exp = prefix[L-1], cycle = 1;
		all[0] = 1;
		for (int i = 1, val = 1; i <= 16; i++) {
			val = add(val, exp);
			all[i] = val;
			if (all[i] == all[1] && i != 1) {
				cycle = i - 1;
				break;
			}
//			printf("c %d ", all[i]);
		}
//		puts("");
//		printf("%d\n", cycle);
			
		for (int i = 0; i <= cycle; i++) {
			for (int j = 0; j < L; j++) {
				preSt[j][i] = add(all[i], prefix[j]);
				sufSt[j][i] = add(suffix[j], all[i]);
			}
		}
		
		int ok = solve(cycle);

//		printf("%d\n", ok);
		printf("Case #%d: %s\n", ++cases, ok ? "YES" : "NO");
	}
	return 0;
}
/*
9
3 1
ijk

5
2 1
ik
3 1
ijk
3 1
kji
2 6
ji
1 10000
i

*/
