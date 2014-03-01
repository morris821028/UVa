#include<stdio.h>
#define HAND 131071
struct {
	int num, l;
	int next;
}NODE[3000];
int size, HASH[HAND+1];
void FreeAll() {
    int i;
    for(i = 0, size = 1; i <= HAND; i++)
        HASH[i] = 0;
}
void insHASH(int n, int l) {
    static int m, pre, now;
    m = n&HAND;
    pre = 0, now = HASH[m];
    while(now) {
        if(NODE[now].num == n && NODE[now].l == l)
            return ;
        else if(NODE[now].num < n || (NODE[now].num == n && NODE[now].l < l))
            pre = now, now = NODE[now].next;
        else    break;
    }
    NODE[size].num = n, NODE[size].l = l;
    NODE[size].next = now;
    if(pre)    NODE[pre].next = size;
    else    HASH[m] = size;
    size++;
}
int findHASH(int n, int l) {
	static int m, pre, now;
    m = n&HAND;
    pre = 0, now = HASH[m];
    while(now) {
        if(NODE[now].num == n && NODE[now].l == l)
            return 1;
        else if(NODE[now].num < n || (NODE[now].num == n && NODE[now].l < l))
            pre = now, now = NODE[now].next;
        else    break;
    }
    return 0;
}
void Build() {
	FreeAll();
	int i, j, k, tmp;
	for(i = 1; i <= 10; i++) {
		k = (1<<i)-1;
		for(j = 0; j <= k; j++) {
			tmp = j | (j << i) | (j << (2*i));
			insHASH(tmp, i*3);
		}
	}
}
int n, Ans, C = 0;
char s[35];
void DFS(int n, char *s, int idx) {
	int i;
	for(i = 3; i <= idx; i+=3) {
		if(findHASH(n&((1<<i)-1), i))
			return;
	}
	if(*s == '\0') {
		Ans++;return;
	}
	if((*s) == '1' || (*s) == '0') {
		DFS((n<<1)|((*s)-'0'), s+1, idx+1);
	} else {
		DFS((n<<1)|0, s+1, idx+1);
		DFS((n<<1)|1, s+1, idx+1);
	}
}
main() {
	Build();
	while(scanf("%d", &n) == 1 && n) {
		Ans = 0;
		scanf("%s", s);
		DFS(0, s, 0);
		printf("Case %d: %d\n", ++C, Ans);
	}
	return 0;
}
