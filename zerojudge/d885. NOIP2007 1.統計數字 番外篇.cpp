#include<stdio.h>
#include<stdlib.h>
#define HAND (1<<17)-1
int HASH[HAND+1], size;
typedef struct {
    int tag, time, next;
} list;
list NODE[100002];
void FreeAll() {
	int a;
	for(a = 0, size = 1; a <= HAND; a++)
		HASH[a] = 0;
}
void insHASH(int n) {
	int m = n&HAND;
	int pre = 0, now = HASH[m];
	while(now) {
		if(NODE[now].tag == n) {NODE[now].time++; return;}
		else if(NODE[now].tag < n)
			pre = now, now = NODE[now].next;
		else	break;
	}
	NODE[size].time = 1, NODE[size].tag = n;
	NODE[size].next = now;
	if(pre) NODE[pre].next = size;
	else	HASH[m] = size;
	size++;
}
int cmp(const void *a, const void *b) {
	list *aa, *bb;
	aa = (list *)a, bb = (list *)b;
	return aa->tag > bb->tag;
}
main() {
	int x, n, a;
	while(scanf("%d", &n) == 1) {
		FreeAll();
		for(a = 0; a < n; a++)
			scanf("%d", &x), insHASH(x);
		qsort(NODE+1, size-1, sizeof(list), cmp);
		for(a = 1; a < size; a++)
			printf("%d %d\n", NODE[a].tag, NODE[a].time);
	}
	return 0;
}
