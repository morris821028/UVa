#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

char data[10010][128];
int colPos[10010][16];
int hashCode[10010][16];
struct cmp {
	static int C1, C2;
	bool operator() (const pair< pair<int, int>, int>& a, 
						const pair< pair<int, int>, int>& b) const {
		if(a.first != b.first)	return a.first < b.first;
		int t;
		t = strcmp(data[a.second] + colPos[a.second][C1],
						data[b.second] + colPos[b.second][C1]);
		if(t)	return t < 0;
		t = strcmp(data[a.second] + colPos[a.second][C2],
						data[b.second] + colPos[b.second][C2]);
		if(t)	return t < 0;
		return false;
	}
};
int cmp::C1 = 0;
int cmp::C2 = 0;
int main() {
	int n, m;
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	while(scanf("%d %d", &n, &m) == 2) {
		while(getchar() != '\n');
		for(int i = 0; i < n; i++) {
			gets(data[i]);
			for(int j = 0, pos = 0; j < m; j++) {
				colPos[i][j] = pos;
				int hash = 0;
				while(data[i][pos] != ',' && data[i][pos] != '\0')
					hash = ((hash<<15) + data[i][pos])&32767, pos++;
				hashCode[i][j] = hash;
				data[i][pos] = '\0', pos++;
			}
		}
		
		pair< pair<int, int>, int> D[10010];
		int flag = 0, r1, r2, c1, c2;
		for(int i = 0; i < m; i++) {
			for(int j = i + 1; j < m; j++) {
				for(int k = 0; k < n; k++) { // (hashCode[k][i], hashCode[k][j])
					D[k] = make_pair(make_pair(hashCode[k][i], hashCode[k][j]), k);
				}
				cmp::C1 = i, cmp::C2 = j;
				sort(D, D + n, cmp());
				for(int k = 1; k < n; k++) {
					if(!cmp()(D[k], D[k-1]) && !cmp()(D[k-1], D[k])) {
						flag = 1;
						r1 = D[k-1].second, r2 = D[k].second;
						c1 = i, c2 = j;
						i = j = m;
						break;
					}
				}
			}
		}
		puts(flag ? "NO" : "YES");
		if(flag)
			printf("%d %d\n%d %d\n", r1 + 1, r2 + 1, c1 + 1, c2 + 1);
	}
	return 0;
}
