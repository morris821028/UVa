#include <bits/stdc++.h>
using namespace std;

struct router {
	vector< vector<string> > e;
	router() {
		
	}
};
int main() {
	int cases = 0;
	int M, Q;
	while (scanf("%d", &M) == 1) {
		map<string, router> route;
		for (int i = 0; i < M; i++) {
			char S[32], tS[32];
			int I;
			scanf("%s %d", S, &I);
			router &info = route[S];
			for (int j = 0; j < I; j++) {
				vector<string> vec;
				for (int k = 0; k < 5; k++)
					scanf("%s", tS), vec.push_back(tS);
				info.e.push_back(vec);
			}
		}
		
		printf("Scenario # %d\n", ++cases);
		scanf("%d", &Q);
		for (int cases = 1; cases <= Q; cases++) {
			vector<string> config;
			char S[32], tS[32];
			for (int i = 0; i < 5; i++)
				scanf("%s", tS), config.push_back(tS);
			
			set<string> visited;
			visited.insert(config[0]);
			while (true) {
				router &info = route[config[0]];
				int next_flag = 0;
				string next;
				for (int i = 0; i < info.e.size(); i++) {
					int ok = 1;
					for (int j = 1; j < 5 && ok; j++) {
						if (info.e[i][j] != "*" && info.e[i][j] != config[j])
							ok = 0;
					}
					if (ok) {
						next = info.e[i][0];
						next_flag = 1;
						break;
					}
				}
				if (next_flag == 1) {
					if (next == config[0]) {
						printf("%d -- delivered to %s\n", cases, config[0].c_str());
						break;
					} else if (visited.count(next)) {
						printf("%d -- circular routing detected by %s\n", cases, next.c_str());
						break;
					}
					config[0] = next, visited.insert(next);
				} else {
					printf("%d -- unable to route at %s\n", cases, config[0].c_str());
					break;
				}
			}
		}
		
		puts("");
	}
	return 0;
}
