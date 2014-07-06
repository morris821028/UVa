#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

int L, W, N, M;
vector< pair<int, int> > LEFT, RIGHT, D;
int find_flag; 
pair<int, int> path[128], pick[128];
int check(int n) {
	double LL, LR, RL, RR;
	LL = LR = RL = RR = 0;
	LL = RR = (L/2.0 - 1.5) * (L/2.0 - 1.5) * W / (double)L / 2;
	LR = RL = (L/2.0 + 1.5) * (L/2.0 + 1.5) * W / (double)L / 2;
	for(int i = 0; i < M; i++) {
		if(pick[i].first < -1.5) {
			LL += fabs(pick[i].first - (-1.5)) * pick[i].second;
		} else {
			LR += fabs(pick[i].first - (-1.5)) * pick[i].second;
		}
		if(pick[i].first < 1.5) {
			RL += fabs(pick[i].first - (1.5)) * pick[i].second;
		} else {
			RR += fabs(pick[i].first - (1.5)) * pick[i].second;
		}
	}
	for(int i = 0; i <= n; i++) {
		if(path[i].first < -1.5) {
			LL += fabs(path[i].first - (-1.5)) * path[i].second;
		} else {
			LR += fabs(path[i].first - (-1.5)) * path[i].second;
		}
		if(path[i].first < 1.5) {
			RL += fabs(path[i].first - (1.5)) * path[i].second;
		} else {
			RR += fabs(path[i].first - (1.5)) * path[i].second;
		}
	}
	return LL <= LR && RR <= RL;
}
void dfs(int l, int r, int dep) {
	if(l == LEFT.size() && r == RIGHT.size()) {
		find_flag = 1;
		for(int i = dep-1; i >= 0; i--)
			printf("%d %d\n", path[i].first, path[i].second);		
		for(int i = 0; i < M; i++)
			printf("%d %d\n", pick[i].first, pick[i].second);
		return;
	}
	if(l < LEFT.size()) {
		path[dep] = D[LEFT[l].second];
		if(check(dep))
			dfs(l+1, r, dep+1);
		if(find_flag)	return;
	}
	if(r < RIGHT.size()) {
		path[dep] = D[RIGHT[r].second];
		if(check(dep))
			dfs(l, r+1, dep+1);
		if(find_flag)	return;
	}
}
int main() {
	int cases = 0, p, q;
	while(scanf("%d %d %d", &L, &W, &N) == 3 && L + W + N) {
		LEFT.clear(), RIGHT.clear(), D.clear();
		M = 0;
		for(int i = 0; i < N; i++) {
			scanf("%d %d", &p, &q);
			D.push_back(make_pair(p, q));
			if(abs(p) < 1.5) {
				pick[M++] = make_pair(p, q);
				continue;
			}
			if(p < 0) {
				LEFT.push_back(make_pair((fabs(2*p) - 3) * q, i));
			} else {
				RIGHT.push_back(make_pair((fabs(2*p) - 3) * q, i));
			}
		}
		sort(LEFT.begin(), LEFT.end());
		sort(RIGHT.begin(), RIGHT.end());
		find_flag = 0;
		printf("Case %d:\n", ++cases);
		dfs(0, 0, 0);
		if(!find_flag)
			puts("Impossible");
	}	
	return 0;
}
/*
20 3 6
-8 4
-4 10
-3 10
2 4
5 7
8 8

20 3 15
1 10 
8 5
-6 8
5 9
-8 4
8 10
-3 10
-4 5
2 9
-2 2
3 3
-3 2
5 1
-6 1
2 5
*/
