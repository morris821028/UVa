#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
int g[32][32] = {}, score[32], n;
int brank[32], wrank[32];
vector< pair<int, int> > game;
void dfs(int idx) {
	if (idx == game.size()) {
		vector< pair<int, int> > board;
		int r;
		for (int i = 0; i < n; i++)
			board.push_back(make_pair(score[i], i));
		sort(board.begin(), board.end(), greater< pair<int, int> >());
		for (int i = 0; i < n; i++) {
			r = (int)(lower_bound(board.begin(), board.end(), make_pair(score[i], 0x3f3f3f3f), greater< pair<int, int> >()) 
						- board.begin());
			brank[i] = min(brank[i], r);
			r = (int)(upper_bound(board.begin(), board.end(), make_pair(score[i], -1), greater< pair<int, int> >()) 
						- board.begin());
			wrank[i] = max(wrank[i], r);
		}
		return ;
	}
	int x = game[idx].first, y = game[idx].second;
	score[x] += 3;
	dfs(idx+1);
	score[x] -= 3;
	
	score[y] += 3;
	dfs(idx+1);
	score[y] -= 3;
	
	score[x]++, score[y]++;
	dfs(idx+1);
	score[x]--, score[y]--;
}
int main() {
	char s[128];
	int cases = 0;
	int m, x, y, a, b;
	string name[128];
	while (scanf("%d", &n) == 1 && n) {
		map<string, int> R;
		memset(g, 0, sizeof(g));
		memset(score, 0, sizeof(score));
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			R[s] = i, name[i] = s;
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s", s);
			x = R[s];
			scanf("%s", s);
			y = R[s];
			g[x][y]++, g[y][x]++;
			scanf("%d %d", &a, &b);
			if (a < b)		score[y] += 3;
			else if (a > b)	score[x] += 3;
			else			score[x]++, score[y]++;
		}
		
		for (int i = 0; i < n; i++)
			brank[i] = 0x3f3f3f3f, wrank[i] = -1;
		game.clear();
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				for (int k = 0; k < 2 - g[i][j]; k++) {
					game.push_back(make_pair(i, j));
				}
			}
		}
		dfs(0);
		printf("Group #%d\n", ++cases);
		for (int i = 0; i < n; i++) {
			printf("%s %d-%d\n", name[i].c_str(), brank[i] + 1, wrank[i]);
		}
		puts("");
	}
	return 0;
}
