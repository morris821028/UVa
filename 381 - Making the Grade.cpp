#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase;
	int S, T;
	int test[105][105], bonus[105], absent[105];
	int G[105];
	scanf("%d", &testcase);
	puts("MAKING THE GRADE OUTPUT");
	while(testcase--) {
		scanf("%d %d", &S, &T);
		for(int i = 0; i < S; i++) {
			for(int j = 0; j < T; j++) {
				scanf("%d", &test[i][j]);
			}
			scanf("%d %d", &bonus[i], &absent[i]);
		}
		double avg[105], adjAvg[105];
		double mean = 0, sd = 0, avgG = 0;
		for(int i = 0; i < S; i++) {
			sort(test[i], test[i]+T);
			int start = 0;
			if(T > 2)	start = 1;
			avg[i] = 0;
			for(int j = start; j < T; j++) {
				avg[i] += test[i][j];
			}
			avg[i] /= T - start;
			avg[i] = floor(avg[i]);
			mean += avg[i];
		}
		mean /= S;
		for(int i = 0; i < S; i++) {
			sd += (avg[i] - mean)*(avg[i] - mean);
		}
		sd = sqrt(sd / S);
		if(sd < 1)
			sd = 1;
		for(int i = 0; i < S; i++) {
			adjAvg[i] = avg[i] + (bonus[i]/2)*3;
		}
		for(int i = 0; i < S; i++) {
			if(adjAvg[i] >= mean + sd)
				G[i] = 0;
			else if(adjAvg[i] >= mean)
				G[i] = 1;
			else if(adjAvg[i] >= mean - sd)
				G[i] = 2;
			else 
				G[i] = 3;
		}
		for(int i = 0; i < S; i++) {
			if(absent[i] == 0)
				G[i]--;
			else 
				G[i] += absent[i]/4;
			G[i] = min(max(G[i], 0), 4);
			avgG += 4 - G[i];
		}
		avgG /= S;        
		printf("%.1lf\n", avgG);
	}
	puts("END OF OUTPUT");
	return 0;
}
/*
10
5 3
100 100 80 3 2
80 80 80 0 5
60 20 70 5 3
40 40 40 5 0
100 20 20 1 9

3
3 2
100 50 2 5
60 60 17 1
20 10 0 0
5 5
100  80  90  80  90   0   0
80 80 80 80 80   0 0
50 50 50 50 50 0 0
100 100 20 20 20 0 0
30 30 30 30 30 0 0
10  4
79   56   59   89    4    5
100   89   96   79    6    2
80   80   80   76    1    3
76   76   76   76    5    4
58   78   67   75    4    0
100   96  100   95    1    2
47   49   46   45    0    5
67   98   59   87    5    5
23   45   52   54    2    7
78   75   79   79    3    3
*/
