#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

double x[64], y[64], sat[64];
double g[64][64], dist[64][64];
char str_id[64][64];
char line[1024], sa[64], sb[64];
vector<int> vg[64];

struct State {
	unsigned long long used;
	int now;
	double sat, h, time;
	vector<int> path;
	bool operator<(const State &other) const {
		return h > other.h;
	}
};
int main() {
	int n, m, cases = 0;
	scanf("%*s");
	while (scanf("%d %d", &n, &m) == 2) {
		while (getchar() != '\n');
		map<string, int> R;
		for (int i = 0; i < n; i++) {
			gets(line);
			sscanf(line, "%lf %lf %lf %s", &x[i], &y[i], &sat[i], &str_id[i]);
			R[str_id[i]] = i;
			vg[i].clear();
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				g[i][j] = dist[i][j] = 1e+30;
			g[i][i] = dist[i][i] = 0;
		}
		for (int i = 0; i < m; i++) {
			scanf("%s %s", sa, sb);
			int u = R[sa], v = R[sb];
			g[u][v] = g[v][u] = hypot(x[u]-x[v], y[u]-y[v]);
			vg[u].push_back(v);
			vg[v].push_back(u);
			dist[u][v] = dist[v][u] = g[v][u];
		}
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
		scanf("%*s");
		printf("MAP %d\n", ++cases);
		while (scanf("%s", line) == 1 && line[0] != 'M') {
			int h1, m1, h2, m2;
			double target_sat, time;
			sscanf(line, "%d:%d", &h1, &m1);
			scanf("%s %d:%d %s %lf", sa, &h2, &m2, sb, &target_sat);
			int from = R[sa], to = R[sb];
			if (h1 * 60 + m1 > h2 * 60 + m2)
				h2 += 24;
			time = h2 * 60 + m2 - (h1 * 60 + m1);
			priority_queue< State, vector<State> > pQ;
			State u, ret;
			u.path.resize(1);
			u.path[0] = -(from + 1);
			u.used = 1LL<<from, u.now = from, u.sat = 0, u.time = 0;
			u.h = fabs(target_sat - (u.sat - dist[u.now][to] * 15));
			pQ.push(u);
			u.path[0] = (from + 1);
			u.used = 1LL<<from, u.now = from, u.sat = sat[from], u.time = 15;
			u.h = fabs(target_sat - (u.sat - dist[u.now][to] * 15));
			pQ.push(u);
			int ok = 0;
			while (!pQ.empty() && !ok) {
				u = pQ.top(), pQ.pop();
//				printf("%lf %d %llu\n", u.h, u.now, u.used);
//				getchar();
				if (u.now == to && fabs(target_sat - u.sat) < 0.1) {
					ret = u, ok = 1;
					break;
				}
				for (int i = 0; i < vg[u.now].size(); i++) {
					int next = vg[u.now][i];
					if ((u.used>>next)&1)	continue;
					if (u.time + dist[u.now][next] * 15 > time)
						continue;
					State v;
//					printf("%lf %lf\n", u.time, g[u.now][next] * 15);
					if (next == to) {
						v = u;
						v.path.push_back(next + 1);
						v.used |= (1LLU<<next), v.time += dist[u.now][next] * 15;
						v.sat += -g[u.now][next] * 15, v.now = next;
						v.h = fabs(target_sat - (v.sat - dist[v.now][to] * 15));
						if (next == to && fabs(target_sat - v.sat) < 0.1) {
							ret = v, ok = 1;
							break;
						}
					} else if (u.time + dist[u.now][next] * 15 + dist[next][to] * 15 + 15 <= time) { // enter
						v = u;
						v.path.push_back((next + 1));
						v.used |= (1LLU<<next), v.time += dist[u.now][next] * 15 + 15;
						v.sat += sat[next] - g[u.now][next] * 15, v.now = next;
						v.h = fabs(target_sat - (v.sat - dist[v.now][to] * 15));
						pQ.push(v);
//						printf("enter %d %d\n", u.now, next);
					}
					if (next != to && u.time + dist[u.now][next] * 15 + dist[next][to] * 15 <= time) { // pass
						v = u;
						v.path.push_back(-(next + 1));
						v.used |= (1LLU<<next), v.time += dist[u.now][next] * 15;
						v.sat += -g[u.now][next] * 15, v.now = next;
						v.h = fabs(target_sat - (v.sat - dist[v.now][to] * 15));
						if (next == to && fabs(target_sat - v.sat) < 0.1) {
							ret = v, ok = 1;
							break;
						}
						pQ.push(v);
//						printf("pass %d %d\n", u.now, next);
					}
				}
			}
			if (ret.path.size() == 0) {
				puts("Impossible!");
			} else {
				printf("PATH FOUND: %.3lf ", ret.sat);
				for (int i = 0; i < ret.path.size(); i++) {
					if (ret.path[i] < 0)	putchar('!');
					printf("%s%c", str_id[abs(ret.path[i])-1], i == ret.path.size() - 1 ? '\n' : ' ');
				}
			}
		}
	}
	return 0;
}
/*
MAP 19 40
0 0 0 UPV Universitat Politecnica de Valencia
5 5 0 SPV Contest hotel
0 1 35 B01 The Object
1.1 1 42 B02 Opera
0.6 1.7 33 B03 New York
1.3 2 55 B04 Blue Note
1.5 2.5 23 B05 The Popes
2.5 2 13 B06 Petrol
4 3.5 12 B07 King of Kings
1.1 4 14 B08 O Salati
1.2 4.5 13 B09 The Snails
2.5 3.5 34 B10 The Earth
1.5 1.5 55 B11 Cafe Coffee
3 4.5 31 B12 Vermouth house
4.5 2.5 45 B13 Jamon Session
1.3 3.6 24 B14 Let's go to eat
1.5 4 34 B15 I'm hungry
0.6 2.5 53 B16 The Gecko
3.5 2.5 43 B17 The Black Sheep
UPV B01
B01 B02
B01 B03
B01 B16
B02 B03
B02 B11
B16 B08
B16 B14
B16 B03
B03 B04
B03 B11
B04 B11
B04 B16
B04 B05
B05 B14
B08 B09
B08 B15
B08 B14
B11 B06
B14 B15
B05 B06
B05 B16
B05 B10
B15 B09
B15 B10
B09 B12
B06 B10
B06 B17
B10 B07
B10 B17
B10 B12
B10 B14
B12 B15
B12 B07
B12 SPV
B17 B07
B17 B13
B07 B13
B07 SPV
B13 SPV
ARRIVALS
23:00 UPV 03:00 SPV 9.0
23:00 UPV 03:00 SPV 8.0
23:00 UPV 03:00 SPV 7.0
23:00 UPV 03:00 SPV 6.0
23:00 UPV 03:00 SPV 5.0
23:00 UPV 03:00 SPV 4.0
23:00 UPV 03:00 SPV 3.0
23:00 UPV 03:00 SPV 2.0
23:00 UPV 03:00 SPV 1.0
23:00 UPV 03:00 SPV 0.0
23:00 UPV 03:00 SPV -1.0
23:00 UPV 03:00 SPV -2.0
23:00 UPV 03:00 SPV -30.0
23:00 UPV 03:00 SPV -40.0
23:00 B05 03:00 B10 40.0
23:00 B05 03:00 B10 30.0
23:00 B05 03:00 B10 20.0
23:00 B05 03:00 B10 10.0
23:00 B05 03:00 B10 0.0
23:00 B05 03:00 B10 -10.0
23:00 B05 03:00 B10 -20.0
23:00 B05 03:00 B10 -30.0
23:00 B05 03:00 B10 -40.0
MAP 2 1
0 0 0 UPV Universitat Politecnica de Valencia
10 10 0 SPV Hotel Silken Puerta de Valencia
UPV SPV
ARRIVALS
23:00 UPV 1:00 SPV 9.0
23:00 UPV 1:00 SPV 8.0
*/
