#include<stdio.h>
char mark[270000] = {}, ans[270000], best[270000], dir[4] = {3,0,1,2}, dirp[4] = {-3,1,1,1};
int next[270000] = {};
int s4[10] = {1}; 
char Map[10][7] = {{}, 
				 {1,2,4,5,0},
				 {1,2,3,0},
				 {2,3,5,6,0},
				 {1,4,7,0},
				 {2,4,5,6,8,0},
				 {3,6,9,0},
				 {4,5,7,8,0}, 
				 {7,8,9,0},
				 {5,6,8,9,0} 
				}; 
void Change(int N, int flag, char C[]) {
	while(N) {
		C[flag] = N%4, N /= 4, flag++;
	} 
} 
void Build() {
	int a, b, c, qt = 0, t, p, Queue[270000];
	Queue[qt++] = 0, best[0] = 0, ans[0] = 10, mark[0] = 1; 
	for(a = 0; a < qt; a++) {
		t = Queue[a], p;
		char C[10] = {}; 
		Change(t, 0, C); 
		for(b = 1; b < 10; b++) {
			for(c = 0, p = t; Map[b][c]; c++) {
				p -= s4[Map[b][c]-1] * dirp[C[Map[b][c]-1]]; 
			} /*c*/ 
			if(mark[p] == 0) {
				mark[p] = 1,Queue[qt++] = p; 
				next[p] = t, best[p] = best[t] + 1, ans[p] = b+'0'; 
			} 
			else {
				if(best[p] > best[t]+1) {
					Queue[qt++] = p; 
					next[p] = t, best[p] = best[t] + 1, ans[p] = b;	
				} 
			} 
		} /*b*/ 
	} /*a*/ 
}
void Print(int now) {
	if(now) {
		Print(next[now]);
		putchar(ans[now]), putchar(' '); 
	} 
} 
main() {
	int t, a, s, x;
	for(a = 1; a < 10; a++) 
		s4[a] = s4[a-1] * 4; 
	Build(); 
	scanf("%d", &t);
	while(t--) {
		for(a = 0, s = 0; a < 9; a++) {
			scanf("%d", &x); 
			s += x * s4[a]; 
		} 
		Print(s), puts(""); 
	} 
	return 0; 
} 
