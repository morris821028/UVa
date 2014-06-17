#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int T, n, map[20][20];
struct Heap {
	unsigned int state[5];
	short Fx;
	char x, y;
}Heap[500000], tmp;
int L;
void Swap(int P, int S) {
	tmp = Heap[P], Heap[P] = Heap[S], Heap[S] = tmp;
}
void siftUp(int site) {
	static int S, P;
	S = site, P = S>>1;
	while(S >= 2 && Heap[P].Fx < Heap[S].Fx) 
		Swap(P, S), S = P, P = S>>1;
}
void siftDown(int site) {
	static int S, P;
	P = site, S = P<<1;
	while(S <= L) {
		if(S < L && Heap[S+1].Fx > Heap[S].Fx)
			S++;
		if(Heap[P].Fx >= Heap[S].Fx)
			break;
		Swap(P, S), P = S, S = P<<1;
	}
}
void insHeap(unsigned int state[], short Fx, char i, char j) {
	++L;
	memcpy(Heap[L].state, state, sizeof(Heap[L].state));
	Heap[L].Fx = Fx;
	Heap[L].x = i;
	Heap[L].y = j;
	siftUp(L);
}
void delHeap() {
	Swap(1, L), L--;
	siftDown(1);
}
int solve() {
	int i, j, ti, tj, x, y;
	int Fx, Gx, Hx, bit, tx, ty, ttx, tty;
	int X[4] = {0,1,0,-1}, Y[4] = {1,0,-1,0};
	unsigned int state[5];
	char mark1[1001], mark2[1001], tmap[12][12];
	int maxLength = 0;
	
	int Queue[300][2], qidx;
	while(L > 0) {
		memcpy(state, Heap[1].state, sizeof(state));
		x = Heap[1].x, y = Heap[1].y, Fx = Heap[1].Fx;
		memset(mark1, 0, sizeof(mark1));
		delHeap();

		Gx = 0;
		for(i = 0; i < 5; i++) {
			for(j = 0; j < 32; j++) {
				if((state[i]&(1<<j)) != 0) {
					bit = i*32+j;
					tx = bit/n, ty = bit%n;
					mark1[map[tx][ty]] = 1;
					Gx++;
				}
			}
		}
		maxLength = maxLength > Gx ? maxLength : Gx;
		if(Fx == Gx)	break;

		for(i = 0; i < 4; i++) {
			tx = x+X[i], ty = y+Y[i];
			if(tx >= 0 && tx < n && ty >= 0 && ty < n) {
				if(mark1[map[tx][ty]] == 1)
					continue;
				bit = tx*n+ty;
				Hx = 0;
				memset(tmap, 0, sizeof(tmap));		
				memset(mark2, 0, sizeof(mark2));
				qidx = -1, Queue[++qidx][0] = tx, Queue[qidx][1] = ty;
				tmap[tx][ty] = 1, mark2[map[tx][ty]] = 1;
				for(ti = 0; ti <= qidx; ti++) {
					tx = Queue[ti][0], ty = Queue[ti][1];
					for(tj = 0; tj < 4; tj++) {
						ttx = tx+X[tj], tty = ty+Y[tj];
						if(ttx >= 0 && ttx < n && tty >= 0 && tty < n) {
							if(mark1[map[ttx][tty]] == 1)
								continue;
							if(mark2[map[ttx][tty]] == 0) {
								Hx++;
								mark2[map[ttx][tty]] = 1;
							}
							if(tmap[ttx][tty] == 0) {
								++qidx;
								Queue[qidx][0] = ttx;
								Queue[qidx][1] = tty;
								tmap[ttx][tty] = 1;
							}
						}
					}
				}
				if(Gx+Hx+1 <= maxLength)	continue;
				tx = x+X[i], ty = y+Y[i];
				state[bit/32] |= (1<<(bit%32));
				insHeap(state, Gx+Hx+1, tx, ty);
				state[bit/32] ^= (1<<(bit%32));
			}
		}
	}
	return maxLength;
}
int main() {
	scanf("%d", &T);
	int i, j, k;
	while(T--) {
		scanf("%d", &n);
		L = 0; 
		unsigned int state[5] = {};
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				scanf("%d", &map[i][j]);
				state[(i*n+j)/32] |= (1<<((i*n+j)%32));
				insHeap(state, n*n, i, j);
				state[(i*n+j)/32] ^= (1<<((i*n+j)%32));
			}
		}
		printf("%d\n", solve());
		if(T)	puts("");
	}
    return 0;
}
