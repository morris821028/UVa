#include<stdio.h>
#include<string.h>
#define Mod 100000
#define MaxL 1000000
int HASH[Mod], size;
typedef struct {
	int v, time, next;
}C;
C Node[MaxL];
int insHash(int v) {
	int m = ((v%Mod)+Mod)%Mod;
	int now = HASH[m], pre = 0;
	while(now) {
		if(Node[now].v < v)
			pre = now, now = Node[now].next;
		else if(Node[now].v == v) {
			Node[now].time++;return 1;
		} else {
			break;
		}
	}
	size++;
	if(!pre)	HASH[m] = size;
	else		Node[pre].next = size;
	Node[size].v = v, Node[size].time = 1;
	Node[size].next = now;
	return 0;
}
int main() {
	int n, i;
	memset(HASH, 0, sizeof(HASH));
	size = 0;
	while(scanf("%d", &n) == 1)
		insHash(n);
	for(i = 1; i <= size; i++)
		printf("%d %d\n", Node[i].v, Node[i].time);
    return 0;
}
