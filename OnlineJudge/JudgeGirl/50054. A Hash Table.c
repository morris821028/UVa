#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char buff[1048576];

#define HSIZE 100007
#define MAXN 50005
void **hL[HSIZE];
void *node[MAXN];
int nidx;
void** newNode() {
	void **ret = &node[nidx];
	nidx += 2;
	return ret;
}
int prob_hash(char *s) {
	int sum = 0;
	while (*s) {
		sum += isalpha(*s) ? *s : (*s - '0');
		s++;
	}
	return sum;
}
unsigned int RS_hash(char *s) {
	unsigned int a = 63689, b = 378551;
    unsigned int value = 0;
    for (int i = 0; s[i]; i++) {
		value = value * a + s[i];
		a *= b;
    }
    return value;
}
void insert(char *s) {	
	unsigned int hval = RS_hash(s) % HSIZE;
	void **p = newNode();
	*p = s, *(p+1) = hL[hval];
	hL[hval] = p;
}
int contain(char *s) {
	int hval = RS_hash(s) % HSIZE;
	void **t = hL[hval];
	while (t != NULL) {
		if (!strcmp(*t, s))
			return 1;
		t = *(t+1);
	}
	return 0;
}
int main() {
	int S, N, Q;
	while (scanf("%d %d %d", &S, &N, &Q) == 3) {
		char *bptr = buff;
		
		nidx = 0;
		for (int i = 0; i < HSIZE; i++)
			hL[i] = NULL;
			
		for (int i = 0; i < N; i++) {
			scanf("%s", bptr);
			insert(bptr);
			while (*bptr)	bptr++;
			bptr++;			
		}
		
		char s[128];
		for (int i = 0; i < Q; i++) {
			scanf("%s", s);
			if (contain(s))
				printf("%d\n", prob_hash(s) % S);
			else
				puts("-1");
		}
	}
	return 0;
}


