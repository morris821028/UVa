#include<stdio.h>
#include<string.h>
#define total_state 67108864
#define init 0
char DP[total_state+1];
int Queue[1760896], Qt = -1;
int min(int x, int y) {
	if(x == 0)	return y;
	if(y == 0)	return x;
	return x < y ? x : y;
}
void Front_turn(int state) {
	static int change_state, t1, t2, dice;
	t1 = state&63;
	dice = t1&12;/*001100*/
	dice |= ((t1&32) != 0) | (((t1&16) != 0)<<1) | (((t1&2) != 0)<<5) | (((t1&1) != 0)<<4);
	t1 = (state>>6)&15, t2 = t1;
	if(t1 >= 12 && t1 <= 15)	return;
	t1 += 4;
	change_state = dice | ((state>>10)<<10) | (t1<<6);
	if((state&1) != 0 && (state&(1<<(t2+10))) == 0)
		change_state = (change_state | (1<<(t2+10))) - (1<<4);
	else if((state&1) == 0 && (state&(1<<(t2+10))) != 0)
		change_state = (change_state - (1<<(t2+10))) | (1<<4);
	if(DP[change_state] == init)
		Queue[++Qt] = change_state;
	DP[change_state] = min(DP[change_state], DP[state]+1);
}
void Back_turn(int state) {
	static int change_state, t1, t2, dice;
	t1 = state&63;
	dice = t1&12;/*001100*/
	dice |= (((t1&32) != 0)<<1) | ((t1&16) != 0) | (((t1&2) != 0)<<4) | (((t1&1) != 0)<<5);
	t1 = (state>>6)&15, t2 = t1;
	if(t1 >= 0 && t1 <= 3)	return;
	t1 -= 4;
	change_state = dice | ((state>>10)<<10) | (t1<<6);
	if((state&1) != 0 && (state&(1<<(t2+10))) == 0)
		change_state = (change_state | (1<<(t2+10))) - (1<<5);
	else if((state&1) == 0 && (state&(1<<(t2+10))) != 0)
		change_state = (change_state - (1<<(t2+10))) | (1<<5);
	if(DP[change_state] == init)
		Queue[++Qt] = change_state;
	DP[change_state] = min(DP[change_state], DP[state]+1);
}
void Right_turn(int state) {
	static int change_state = 0, t1, t2, dice;
	t1 = state&63;
	dice = t1&48;/*110000*/
	dice |= (((t1&8) != 0)<<1) | (((t1&4) != 0)) | (((t1&2) != 0)<<2) | (((t1&1) != 0)<<3);
	t1 = (state>>6)&15, t2 = t1;
	if(t1 == 3 || t1 == 7 || t1 == 11 || t1 == 15)	return;
	t1 += 1;
	change_state = dice | ((state>>10)<<10) | (t1<<6);
	if((state&1) != 0 && (state&(1<<(t2+10))) == 0)
		change_state = (change_state | (1<<(t2+10))) - (1<<3);
	else if((state&1) == 0 && (state&(1<<(t2+10))) != 0)
		change_state = (change_state - (1<<(t2+10))) | (1<<3);
	if(DP[change_state] == init)
		Queue[++Qt] = change_state;
	DP[change_state] = min(DP[change_state], DP[state]+1);
}
void Left_turn(int state) {
	static int change_state = 0, t1, t2, dice;
	t1 = state&63;
	dice = t1&48;/*110000*/
	dice |= (((t1&8) != 0)) | (((t1&4) != 0)<<1) | (((t1&2) != 0)<<3) | (((t1&1) != 0)<<2);
	t1 = (state>>6)&15, t2 = t1;
	if(t1 == 0 || t1 == 4 || t1 == 8 || t1 == 12)	return;
	t1 -= 1;
	change_state = dice | ((state>>10)<<10) | (t1<<6);
	if((state&1) != 0 && (state&(1<<(t2+10))) == 0)
		change_state = (change_state | (1<<(t2+10))) - (1<<2);
	else if((state&1) == 0 && (state&(1<<(t2+10))) != 0)
		change_state = (change_state - (1<<(t2+10))) | (1<<2);
	if(DP[change_state] == init)
		Queue[++Qt] = change_state;
	DP[change_state] = min(DP[change_state], DP[state]+1);
}
void process() {
	memset(DP, init, sizeof(DP));
	int i, j, now;
	for(i = 0; i <= 15; i++)
		for(j = 0; j <= 63; j++) {
			DP[(i<<6) | j] = 1;
			Queue[++Qt] = (i<<6) | j;
		}
	for(i = 0; i <= Qt; i++) {
		now = Queue[i];
		Front_turn(now);
		Back_turn(now);
		Right_turn(now);
		Left_turn(now);
	}
}
main() {
	process();
	int t;
	char s[5];
	scanf("%d", &t);
	while(t--) {
		int i, j, state = 0;
		for(i = 0; i < 4; i++) {
			scanf("%s", s);
			for(j = 0; j < 4; j++) {
				if(s[j] == 'X')
					state |= (1<<(i*4+j+10));
				if(s[j] == 'D')
					state += (1<<6)*(i*4+j);
			}
		}
		if(DP[state] == init)
			puts("impossible");
		else
			printf("%d\n", DP[state]-1);
	}
	return 0;
}
