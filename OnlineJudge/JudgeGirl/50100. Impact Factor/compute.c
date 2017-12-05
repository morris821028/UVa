#include "compute.h"
#include <stdio.h>
#include <string.h>
/*
typedef struct {
    char journalName[64];
    int numCitedPaper;
    int citedPaperIndex[1024];
} paper;
*/
#define MAXN 1024
#define MAXS 64
#define MAXBUFF (MAXN*MAXS)
static char sbuf[MAXBUFF], *shead[MAXN];
static int count[MAXN], total[MAXN];
static int cmp(const void *a, const void *b) {
	int x = *(int *) a, y = *(int *) b;
	return strcmp(shead[x], shead[y]);
}
void compute(paper p[], int n) {
	memset(shead, NULL, sizeof(shead));
	memset(count, 0, sizeof(count));
	memset(total, 0, sizeof(total));
	char *sptr = sbuf;
	int m = 0, r[MAXN];
	for (int i = 0; i < n; i++) {
		int pos = -1;
		for (int j = 0; j < m; j++) {
			if (!strcmp(shead[j], p[i].journalName))
				pos = j, j = m;
		}
		if (pos < 0) {
			pos = m;
			strcpy(sptr, p[i].journalName);
			shead[m] = sptr;
			while (*sptr) sptr++;
			sptr++;
			m++;
		}
		r[i] = pos, total[pos]++;
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < p[i].numCitedPaper; j++)
			count[r[p[i].citedPaperIndex[j]]]++;
	}
	
	int A[MAXN];
	for (int i = 0; i < m; i++)
		A[i] = i;
	qsort(A, m, sizeof(int), cmp);
	for (int i = 0; i < m; i++) {
		int x = A[i];
		printf("%s %d/%d\n", shead[x], count[x], total[x]);
	}
}
