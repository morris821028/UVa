#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm> 
using namespace std;

vector< pair<int, int> > factor(int n) {
	vector< pair<int, int> > R;
	for(int i = 2, j; i * i <= n; i++) {
		if(n%i == 0) {
			for(j = 0; n%i == 0; n /= i, j++);
			R.push_back(make_pair(i, j));
		}
	}
	if(n != 1)
		R.push_back(make_pair(n, 1));
	return R;
}
int main() {
	int testcase;
	int n, a, b;
	long long f[50] = {0, 1};
	for(int i = 2; i < 50; i++)
		f[i] = f[i - 1] + f[i - 2];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d", &n, &a, &b);
		map<int, long long> R;
		vector< pair<int, int> > F;
		
		F = factor(a);
		for(vector< pair<int, int> >::iterator it = F.begin();
			it != F.end(); it++)
			R[it->first] += f[n - 1] * it->second;
		F = factor(b);
		for(vector< pair<int, int> >::iterator it = F.begin();
			it != F.end(); it++)
			R[it->first] += f[n] * it->second;
			
		for(map<int, long long>::iterator it = R.begin();
			it != R.end(); it++)
			printf("%d %lld\n", it->first, it->second);
		puts("");
	}
	return 0;
}
/*
2
2 2 3
13 2 3
*/
