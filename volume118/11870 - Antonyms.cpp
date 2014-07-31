#include <stdio.h> 
#include <string.h>
#include <map>
#include <iostream>
using namespace std;
int p[2048], rank[2048];
int findp(int x) {
	return p[x] == x ? x : (p[x]=findp(p[x]));
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if(x == y)	return 0;
	if(rank[x] > rank[y])
		p[y] = x, rank[x] += rank[y];
	else
		p[x] = y, rank[y] += rank[x];
	return 1;
}
int main() {
	int testcase, cases = 0, N, M;
	char s[1024];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &N, &M);
		map<string, int> R;
		int size = 0;
		for(int i = 0; i < 2048; i++)
			p[i] = i, rank[i] = 1;
		for(int i = 0; i < N; i++) {
			scanf("%s", s);
			int &x = R[s];
			if(x == 0)	x = ++size;
			scanf("%s", s);
			int &y = R[s];
			if(y == 0)	y = ++size;
			joint(2 * x, 2 * y);
		}
		int ret = 1;
		for(int i = 0; i < M; i++) {
			scanf("%s", s);
			int &x = R[s];
			if(x == 0)	x = ++size;
			scanf("%s", s);
			int &y = R[s];
			if(y == 0)	y = ++size;
			if(findp(2 * x) == findp(2 * y))
				ret = 0;
			joint(2 * x + 1, 2 * y);
			joint(2 * y + 1, 2 * x);
		}
		printf("Case %d: %s\n", ++cases, ret ? "YES" : "NO");
	}
	return 0;
}
