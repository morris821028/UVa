#include <stdio.h> 
#include <string.h>
#include <vector>
using namespace std;

int main() {
	int K, N, x;
	char institution[1024][32];
	while(scanf("%d %d", &K, &N) == 2) {
		if(K + N == 0)	break;
		vector<int> paper[1024];
		for(int i = 0; i < N; i++) {
			scanf("%s", institution[i]);
			for(int j = 0; j < K; j++) {
				scanf("%d", &x), x--;
				paper[x].push_back(i);
			}
		}
		int prob = 0;
		for(int i = 0; i < N; i++) {
			if(paper[i].size() != K) {
				prob++;
				continue;
			}
			int err = 0, used[1024] = {};
			for(int j = 0; j < K && !err; j++) {
				int u = paper[i][j];
				if(!strcmp(institution[u], institution[i])) // couldn't same institution
					err = 1;
				else if(used[u]) // duplicate view
					err = 1;
				else if(u == i) // itself
					err = 1;
				used[u] = 1;
			}
			prob += err;
		}
		if(prob == 0)
			puts("NO PROBLEMS FOUND");
		else
			printf("%d PROBLEM%s FOUND\n", prob, prob > 1 ? "S" : "");
	}
	return 0;
}
