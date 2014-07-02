#include <stdio.h>
#include <map>
#include <iostream>
#include <queue>
using namespace std;
const string name[5] = {"Ja", "Sam", "Sha", "Sid", "Tan"};
int main() {
	map<string, int> R;
	int testcase, cases = 0;
	int n, m, x;
	char s[1024];
	for(int i = 0; i < 5; i++)
		R[name[i]] = i;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %s", &m, &n, &s);
		int start = R[s], next, ret[5] = {};
		queue<int> ls[5];
		for(int i = 0; i < 5; i++) {
			scanf("%d", &x);
			while(x--) {
				scanf("%s", s);
				ls[i].push(R[s]);
			}
		}
		
		for(int i = 0; i < n; i += m+2) {
			ret[start] += min(n - i, m);
			next = ls[start].front();
			ls[start].push(ls[start].front());
			ls[start].pop();
			start = next;
		}
		
		printf("Case %d:\n", ++cases);
		for(int i = 0; i < 5; i++)
			printf("%s %d\n", name[i].c_str(), ret[i]);
	}
	return 0;
}
