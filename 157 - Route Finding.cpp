#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
int trans_node(int r, int a) {
	r -= 'A', a -= 'a';
	return r * 26 + a;
}
void reverse_node(int n, int &r, int &a) {
	r = n /26 + 'A', a = n %26 + 'a';
}
vector<int> g[1024], g2[1024];
void spfa(int st, int ed) {
	int used[1024][2] = {}, dist[1024][2] = {}, prex[1024][2][2];
	for(int i = 0; i < 1024; i++)
		dist[i][0] = dist[i][1] = 0x3f3f3f3f;
	queue<int> Q, S;
	Q.push(st), S.push(0);
	dist[st][0] = 0, prex[st][0][0] = -1;
	while(!Q.empty()) {
		int u = Q.front(), s = S.front();
		Q.pop(), S.pop();
		used[u][s] = 0;
		for(int i = 0; i < g[u].size(); i++) {
			int v = g[u][i];
			if(dist[v][0] > dist[u][s] + 1) {
				dist[v][0] = dist[u][s] + 1;
				prex[v][0][0] = u, prex[v][0][1] = s;
				if(!used[v][0]) {
					used[v][0] = 1, Q.push(v), S.push(0);
				}
			}
		}
		int cost = (s == 1) ? 0 : 3;
		for(int i = 0; i < g2[u].size(); i++) {
			int v = g2[u][i];
			if(dist[v][1] > dist[u][s] + cost) {
				dist[v][1] = dist[u][s] + cost;
				
				if(cost == 0)
					prex[v][1][0] = prex[u][s][0], prex[v][1][1] = prex[u][s][1];
				else
					prex[v][1][0] = u, prex[v][1][1] = s;

				if(!used[v][1]) {
					used[v][1] = 1, Q.push(v), S.push(1);
				}
			}
		}
	}
	printf("%3d: ", min(dist[ed][0], dist[ed][1]));
	
	int r = -1, a = -1, s, mm = ed;
	if(dist[ed][0] <= dist[ed][1])
		s = 0;
	else
		s = 1;
	do {
		int nr, na;
		reverse_node(mm, nr, na);
		if(nr != r) {
			if(mm != ed)	printf("=");
			printf("%c%c", nr, na);
		} else {
			printf("%c", na);
		}
		int om = mm;
		mm = prex[om][s][0], s = prex[om][s][1];
		r = nr, a = na;
	} while(mm != -1);
	puts("");
}
int main() {
	char line[1024];
	for(int n; scanf("%d", &n) == 1;) {
		for(int i = 0; i < 1024; i++)
			g[i].clear(), g2[i].clear();
		while(n--) {
			scanf("%s", &line);
			int r = line[0], preX;
			preX = trans_node(r, line[2]);
			for(int i = 3; line[i]; i++) {
				if(line[i] != '=') {
					int x = trans_node(r, line[i]);
					int y = preX;
					g[x].push_back(y);
					g[y].push_back(x);
					preX = x;
				} else {
					int x = trans_node(line[i+1], line[i+2]);
					int y = preX;
					g2[x].push_back(y);
					g2[y].push_back(x);
					i += 2;
				}
			}
		}
		while(scanf("%s", line) == 1 && line[0] != '#') {
			int x = trans_node(line[0], line[1]);
			int y = trans_node(line[2], line[3]);
			spfa(y, x);
		}
	}
	return 0;
}
/*
4
A:fgmpnxzabjd=Dbf
D:b=Adac=Ccf
B:acd=Azefg=Cbh
C:bac
AgAa
AbBh
BhDf
#

5 
A:ab=Bbcdefghijk 
B:abc=Ajdef=Cb 
C:ab 
D:cd=Eg 
E:fg=Bf 
AaAk 
AcAk 
AbBb 
BaDd 
# 
*/
