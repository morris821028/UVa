#include <stdio.h> 
#include <string.h>

int main() {
	int N, T, M;
	int time, team;
	char prob[50], judge[50];
	while(scanf("%d %d %d", &N, &T, &M) == 3) {
		int scoreboard[105][25] = {};
		int prob_blood[25], prob_solve[25];
		memset(prob_blood, -1, sizeof(prob_blood));
		while(M--) {
			scanf("%d %d %s %s", &time, &team, &prob, &judge);
			if(judge[0] == 'Y') {
				if(scoreboard[team][prob[0] - 'A'] == 0) {
					scoreboard[team][prob[0] - 'A'] = 1;
					prob_blood[prob[0] - 'A'] = time;
					prob_solve[prob[0] - 'A'] = team;
				} 
			}
		}
		for(int i = 0; i < N; i++) {
			printf("%c ", i + 'A');
			if(prob_blood[i] == -1)
				puts("- -");
			else
				printf("%d %d\n", prob_blood[i], prob_solve[i]);
		}
	}
	return 0;
}
