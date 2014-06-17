#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct Gene {
	int DNA[4], n;
	double h;
	Gene() {
		memset(DNA, 0, sizeof(DNA));
	}
	int GET(int x) {
		return DNA[x>>5]>>((x)&31)&1;
	}
	void SET(int x) {
		DNA[x>>5] |= 1<<((x)&31);
	}
	void NSET(int x) {
		DNA[x>>5] ^= 1<<((x)&31);
	}
	Gene crossover(Gene y) {
		int p = rand()%n;
		for(int i = p; i < n; i++) {
			int a = GET(i), b = y.GET(i);
			if(a != b) {
				y.NSET(i);
			}
		}
		return y;
	}
	void mutation() {
		int p = rand()%n;
		NSET(p);
	}
	double fitness(double w[], double k) {
		double c = -k;
		for(int i = 0; i < n; i++) {
			if(GET(i))
				c += w[i];
		}
		if(c < 0)	c = -c;
		h = c = 1 - c/k;
		return h;
	}
};
bool cmp(Gene a, Gene b) {
	return a.h < b.h;
}
double randDouble() {
	return (rand() % 32767) / 32767.0;
}
void Genetic_Algorithm(int n, double w[]) {
#define ITERATE 1
#define CREATURE 750 
	Gene Pool[CREATURE], NPool[CREATURE];
	double half = 0;
	for(int i = 0; i < n; i++)
		half += w[i];
	half /= 2.0;
	// init
	for(int i = 0; i < CREATURE; i++) {
		for(int j = 0; j < n; j++) {
			int k = rand()%2;
			if(k)	Pool[i].SET(j);
		}
		Pool[i].n = n;
		Pool[i].fitness(w, half);
	}
	sort(Pool, Pool + CREATURE, cmp);
	Gene bestGene = Pool[CREATURE-1];
	// 
	double board[CREATURE], tot;
	for(int i = 0; i < ITERATE; i++) {
		tot = 0;
		for(int j = 0; j < CREATURE; j++) {
			tot += Pool[j].h;
		}
		board[0] = Pool[0].h / tot;
		for(int j = 1; j < CREATURE; j++) {
			board[j] = board[j-1] + Pool[j].h / tot;
		}
		for(int j = 0; j < CREATURE; j++) {
			int x = lower_bound(board, board + CREATURE, randDouble()) - board;
			int y = lower_bound(board, board + CREATURE, randDouble()) - board;
			NPool[j] = Pool[x].crossover(Pool[y]);
		}
		for(int j = 0; j < CREATURE; j++) {
			Pool[j] = NPool[j];
			if(randDouble() < 0.2)
				Pool[j].mutation();
			Pool[j].n = n;
			Pool[j].fitness(w, half);
		}
		sort(Pool, Pool + CREATURE, cmp);
		if(Pool[CREATURE-1].h < bestGene.h)
			bestGene = Pool[CREATURE-1];
	}
	double out = 0;
	for(int i = 0; i < n; i++) {
		if(bestGene.GET(i))
			out += w[i];
	}
	int f = 0;
	for(int i = 0; i < n; i++) {
		if(out < half) {
			if(bestGene.GET(i)) {
				if(f)	putchar(' ');
				f = 1;
				printf("%d", i+1);
			}
		} else {
			if(!bestGene.GET(i)) {
				if(f)	putchar(' ');
				f = 1;
				printf("%d", i+1);
			}
		}
	}
	puts("");
}
int main() {
	int n;
	double w[105];
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 0; i < n; i++) {
			scanf("%lf", &w[i]);
		}
		Genetic_Algorithm(n, w);
	}
	return 0;
}
