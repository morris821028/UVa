#include <stdio.h> 
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
using namespace std;

const int MAXS = 25;
const int MAXR = 105;
const int MAXN = 512;
map<string, int> Rmap[MAXS];
vector<string> Rvec[MAXS];
void addNode(string s) {
	int len = s.length(), label;
	if (!Rmap[len].count(s)) {
		label = Rmap[len].size();
		Rmap[len][s] = label;
		Rvec[len].push_back(s);
		assert(label < MAXN);
	}
}

// floyd
long long dist[MAXN][MAXN], preDist[MAXN][MAXN];
const long long INF = 1LL<<61;
int main() {
	string A, B, x, y;
	int M, N, cases = 0;
	while (cin >> A >> B >> M) {
		if (A == ".")
			return 0;
		set< pair<string, string> > rules;
		for (int i = 0; i < MAXS; i++)
			Rmap[i].clear(), Rvec[i].clear();
			
		for (int i = 0; i < M; i++) {
			cin >> x >> y;
			rules.insert(make_pair(x, y));
			for (int j = 0; j < x.length(); j++) {
				string s1 = x.substr(j), s2 = y.substr(j);
				addNode(s1), addNode(s2);
			}
		}
		
		N = A.length();
		for (int i = 0; i < N; i++) {
			string s1 = A.substr(i), s2 = B.substr(i);
			addNode(s1), addNode(s2);
		}
		
		for (int p = 1; p <= N; p++) {
			int n = Rmap[p].size();
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j)	
						dist[i][j] = 0;
					else {
						dist[i][j] = INF;
						if (rules.count(make_pair(Rvec[p][i], Rvec[p][j]))) {
							dist[i][j] = min(dist[i][j], 1LL); // rule A -> B, cost 1
						}
						if (p > 1 && Rvec[p][i][0] == Rvec[p][j][0]) { // node Aaaaaa -> Abbbbb, cost aaaaa -> bbbbb
							int pi = Rmap[p-1][Rvec[p][i].substr(1)];
							int pj = Rmap[p-1][Rvec[p][j].substr(1)];
							dist[i][j] = min(dist[i][j], preDist[pi][pj]);
						}
					}
				}
			}
			
			// floyd algorithm
			for (int k = 0; k < n; k++) 
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
						dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			
			// copy for next loop
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					preDist[i][j] = dist[i][j];
		}
		
		int st = Rmap[N][A], ed = Rmap[N][B];
		long long d = dist[st][ed];
		
		printf("Case %d: ", ++cases);
		if (d >= INF)
			printf("No solution\n");
		else
			printf("%lld\n", d);
	}
	return 0;
}
/*
AAAAAAAAAAAAAAAAAAAA BBBBBBBBBBBBBBBBBBBB 20
ABBBBBBBBBBBBBBBBBBB BAAAAAAAAAAAAAAAAAAA
ABBBBBBBBBBBBBBBBBB  BAAAAAAAAAAAAAAAAAA 
ABBBBBBBBBBBBBBBBB   BAAAAAAAAAAAAAAAAA  
ABBBBBBBBBBBBBBBB    BAAAAAAAAAAAAAAAA   
ABBBBBBBBBBBBBBB     BAAAAAAAAAAAAAAA    
ABBBBBBBBBBBBBB      BAAAAAAAAAAAAAA     
ABBBBBBBBBBBBB       BAAAAAAAAAAAAA      
ABBBBBBBBBBBB        BAAAAAAAAAAAA       
ABBBBBBBBBBB         BAAAAAAAAAAA        
ABBBBBBBBBB          BAAAAAAAAAA         
ABBBBBBBBB           BAAAAAAAAA          
ABBBBBBBB            BAAAAAAAA           
ABBBBBBB             BAAAAAAA            
ABBBBBB              BAAAAAA             
ABBBBB               BAAAAA              
ABBBB                BAAAA               
ABBB                 BAAA                
ABB                  BAA                 
AB                   BA                  
A                    B   
*/
