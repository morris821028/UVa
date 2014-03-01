#include<stdio.h>
int next[1000001], pre[100001]; 
int A[1000001], L, set[100001];
char USB[100001]; 
struct  Heap {
    int x, node; 
}Heap[10001];/*max heap*/ 
void Swap(int P, int S) {
    int T; 
    T=Heap[P].x, Heap[P].x=Heap[S].x, Heap[S].x=T;
    T=Heap[P].node, Heap[P].node=Heap[S].node, Heap[S].node=T;
    set[Heap[S].node] = S, set[Heap[P].node] = P; 
}
void siftup (int site) {
    int S = site, P = site >> 1;
    while(S >= 2 && Heap[P].x < Heap[S].x)
		Swap(P, S), S = P, P = S >> 1;
}
void siftdown(int site) {
    int P = site, S = site << 1;
    while(S <= L) {
        if(S < L && Heap[S+1].x > Heap[S].x)	S++;
        if(Heap[P].x >= Heap[S].x)	break;
        Swap(P, S), P = S, S = P << 1; 
    }
}
void ins(int site, int value, int t) {/*insert new node*/ 
	Heap[site].node = value;
	Heap[site].x = next[t]; 
	set[value] = site, USB[value] = 1; 
	siftup(site); 
} 
void del() {/*delete last node*/ 
	Swap(1, L), L--; 
	siftdown(1); 
} 
int Input() { 
    char cha; 
    unsigned int x = 0; 
    while(cha = getchar()) 
        if(cha != ' ' && cha != '\n') break; 
    x = cha-48; 
    while(cha = getchar()) { 
        if(cha == ' ' || cha == '\n') break; 
        x = x*10 + cha-48; 
    } 
    return x; 
}
main() {
	int t, n, m;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		int a, Ans = 0;
		for(a = 0, L = 0; a < 100001; a++) /*initiate*/ 
			pre[a] = 0, USB[a] = 0; 
		
		for(a = 1; a <= n; a++) { 
			A[a] = Input(); 
			if(pre[A[a]])
				next[pre[A[a]]] = a; 
			pre[A[a]] = a; 
		} 

		for(a = 0; a < 100001; a++) 
			if(pre[a])
				next[pre[a]] = n+1;		
		for(a = 1; a <= n; a++) {
			if(USB[A[a]]) {/*heap->p (next adjust)*/
				Heap[set[A[a]]].x = next[a]; 
				siftup(set[A[a]]);
				continue; 
			} 
			if(L == m) {/*pull out*/ 
				Ans++;
				USB[Heap[1].node] = 0;/*max pull out*/ 
				del(); 
			} 
			L++, ins(L, A[a], a); 
		} 
		printf("%d\n", Ans); 
	}
	return 0; 
}
