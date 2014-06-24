#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int n, m, cases = 0, x;
	while(scanf("%d %d", &n, &m) == 2 && n+m) {
		int bad[1024] = {}, A[1024][16];
		int badCount = 0;
		for(int i = 0; i < m; i++) {
			int mark[16] = {};
			for(int j = 0; j < n; j++) {
				scanf("%d", &x);
				A[i][j] = x;
				if(x > n || x < 1) {
					bad[i] = 1;
					continue;
				}
				mark[x]++;
				if(mark[x] > 1)
					bad[i] = 1;
			}
			badCount += bad[i];
		}
		
		printf("Election #%d\n", ++cases);
		printf("   %d bad ballot(s)\n", badCount);
		
		int Atop[1024] = {}, alive[1024] = {}, aliveCount = n;
		for(int i = 1; i < n; i++) {
			int votes[16] = {}, mx = 0, del = -1;
			for(int j = 0; j < m; j++) {
				if(bad[j])	continue;
				while(alive[A[j][Atop[j]]])
					Atop[j]++;
				votes[A[j][Atop[j]]]++;
			}
			for(int j = 1; j <= n; j++)
				mx = max(mx, votes[j]);
			for(int j = 1; j <= n; j++) {
				if(votes[j] < mx && alive[j] == 0)
					del = j, mx = votes[j];
			}
			if(del == -1)	break;
			alive[del] = 1, aliveCount--;
		}
		if(aliveCount == 1) {
			for(int i = 1; i <= n; i++)
				if(alive[i] == 0)
					printf("   Candidate %d is elected.\n", i);
		} else {
			printf("   The following candidates are tied:");
			for(int i = 1; i <= n; i++)
				if(alive[i] == 0)
					printf(" %d", i);
			puts("");
		}
	}
	return 0;
}
