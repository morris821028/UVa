#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define HSIZE 1007
#define HNODE 8192
#define MSIZE 128
#define CSIZE 128
typedef struct Memb {
	char *name;	uint32_t h;
	struct Memb *next;
} Memb;
typedef struct Club {
	char *name;	uint32_t h;
	Memb *memb[MSIZE], *lead;
	struct Club *next;
} Club;
uint32_t hash(char *s) {
	uint32_t ret = 0;
	for (int i = 0; s[i]; i++)
		ret = ret*13 + s[i];
	return ret;
}
char* buff(char *s) {
	static char buf[16777216], *ptr = buf;
	char *ret = ptr;
	while (*s)	*ptr = *s, ptr++, s++;
	*ptr = '\0', ptr++;
	return ret;
}
Club* newClub(char *s) {
	Club *p = (Club *) calloc(1, sizeof(Club));
	p->name = buff(s), p->h = hash(s);
	return p;
}
Club* findClub(Club *C, char *s, uint32_t h) {
	while (C) {
		if (C->h == h && !strcmp(s, C->name))
			return C;
		C = C->next;
	}
	return NULL;
}
Memb* newMemb(char *s) {
	Memb *p = (Memb *) calloc(1, sizeof(Memb));
	p->name = buff(s), p->h = hash(s);
	return p;
}
Memb* findMemb(Club *C, char *s, uint32_t h) {
	Memb *M = C->memb[h%MSIZE];
	while (M) {
		if (M->h == h && !strcmp(s, M->name))
			return M;
		M = M->next;
	}
	return NULL;
}
int main() {
	int n, m;
	char s1[64], s2[64];
	int cmd;
	while (scanf("%d", &n) == 1) {
		Club *C[CSIZE] = {};
		for (int i = 0; i < n; i++) {
			scanf("%d %s %s", &cmd, s1, s2);
			if (!cmd) {
				Club *p = newClub(s2);
				Memb *t = newMemb(s1);
				p->next = C[p->h%CSIZE], C[p->h%CSIZE] = p;
				p->memb[t->h%MSIZE] = p->lead = t;
			} else {
				uint32_t h = hash(s2);
				Club *p = findClub(C[h%CSIZE], s2, h);
				Memb *t = newMemb(s1);
				t->next = p->memb[t->h%MSIZE], p->memb[t->h%MSIZE] = t;
			}
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d", &cmd);
			if (!cmd) {
				scanf("%s", s1);
				uint32_t h = hash(s1);
				Club *p = findClub(C[h%CSIZE], s1, h);
				puts(p == NULL ? "None" : p->lead->name);
			} else {
				scanf("%s %s", s1, s2);
				uint32_t h1 = hash(s1), h2 = hash(s2);
				Club *p = findClub(C[h2%CSIZE], s2, h2);
				Memb *t = p ? findMemb(p, s1, h1) : NULL;
				puts(p == NULL ? "-1" : (t == NULL ? "0" : "1"));
			}
		}
	}
	return 0;
}
