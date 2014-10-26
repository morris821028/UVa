#include <stdio.h> 
#include <string.h>
#define MAXN 1024
#define MAX_TAPE 1000
struct State {
	int next[2][3]; // next state, tape, move
	void init() {
		memset(next, -1, sizeof(next));
	}
} states[MAXN];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n+m) {
		for (int i = 0; i < MAXN; i++)
			states[i].init();
		int qprev, cprev, qnext, cnext;
		int IN, OUT;
		char mov[8];
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d %d %s", &qprev, &cprev, &qnext, &cnext, mov);
			states[qprev].next[cprev][0] = qnext;
			states[qprev].next[cprev][1] = cnext;
			states[qprev].next[cprev][2] = mov[0] == 'L' ? -1 : 1;
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &IN, &OUT);
			int tape[MAX_TAPE] = {}, out_tape[MAX_TAPE] = {};
			for (int j = 0; j < IN; j++)
				tape[j] = 1;
			for (int j = 0; j < OUT; j++)
				out_tape[j] = 1;
			int runtime = 0, state = 0, tape_pos = 0;
			int nstate;
			for (runtime = 0; runtime < 10000; runtime++) {
				int *st = states[state].next[tape[tape_pos]];
				state = st[0];
				if (state == -1) // halt
					break;
				tape[tape_pos] = st[1];
				tape_pos += st[2];
				if (tape_pos < 0 || tape_pos >= MAX_TAPE)
					break;
			}
			if (tape_pos < 0 || tape_pos >= MAX_TAPE)
				puts("MLE");
			else if (runtime >= 10000)
				puts("TLE");
			else {
				puts(memcmp(tape, out_tape, sizeof(tape)) ? "WA" : "AC");
			}
		}
	}
	return 0;
}
