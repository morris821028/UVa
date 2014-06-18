#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int n;
double A[705][705];
int L[705], R[705];
vector< pair<int, double> > dfs(int races) {
	vector< pair<int, double> > ret;
	if(races <= n) {
		ret.push_back(make_pair(races, 1));
		return ret;
	}
	vector< pair<int, double> > l = dfs(L[races]);
	vector< pair<int, double> > r = dfs(R[races]);
	for(int i = 0; i < l.size(); i++) {
		double p = 0;
		for(int j = 0; j < r.size(); j++)
			p += l[i].second * r[j].second * A[l[i].first][r[j].first];
		ret.push_back(make_pair(l[i].first, p));
	}
	for(int i = 0; i < r.size(); i++) {
		double p = 0;
		for(int j = 0; j < l.size(); j++)
			p += l[j].second * r[i].second * A[r[i].first][l[j].first];
		ret.push_back(make_pair(r[i].first, p));
	}
	return ret;
	
}
int main() {
	while(scanf("%d", &n) == 1 && n) {
		int i, j;
		for(i = 1; i <= n; i++)
			for(j = 1; j <= n; j++)
				scanf("%lf", &A[i][j]);
		int indeg[705] = {};
		for(i = n + 1; i < 2*n; i++) {
			scanf("%d %d", &L[i], &R[i]);
			indeg[L[i]]++, indeg[R[i]]++;
		}
		vector< pair<int, double> > ret;
		for(i = 1; i < 2*n; i++) {
			if(indeg[i] == 0) {
				ret = dfs(i);
				break;
			} 
		}
		for(i = 0; i < ret.size(); i++)
			if(ret[i].first == 1)
				printf("%.6lf\n", ret[i].second);
	}
	return 0;
}
