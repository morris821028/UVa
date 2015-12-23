#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define swap(x, y) {int t; t = x, x = y, y = t;}
int fsize(FILE *fp) {
	int prev = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, prev, SEEK_SET);
	return size;
}
#define USAGEMEM (2<<20)
#define MAXELE ((2<<20)/4)
int A[MAXELE];
#define HSIZE 100007
#define HNODE 32767
typedef struct HashNode {
    int f, cnt;
    struct HashNode *next;
} HashNode;
HashNode *hhead[HSIZE], hnodes[HNODE];
int nodesize = 0;
int cmp(const void *x, const void *y) {
	return ((HashNode*) x)->f - ((HashNode*) y)->f;
}
unsigned int hash(int f) {
    unsigned int a = 63689, b = 378551;
    unsigned int value = 0;
    value = value * a + f, a = a * b;
    return value;
} 
void initHash() {
    memset(hhead, 0, sizeof(hhead));
    nodesize = 0;
}
int insertHash(int f) {
    unsigned int hidx = hash(f)%HSIZE;
    for (HashNode *p = hhead[hidx]; p != NULL; p = p->next) {
        if (f == p->f) {
        	p->cnt++;
            return 1;
        }
    }
    if (nodesize >= HNODE)	return 0;
    HashNode s = {.f = f, .cnt = 1, .next = NULL};
    hnodes[nodesize] = s;
    hnodes[nodesize].next = hhead[hidx];
    hhead[hidx] = &hnodes[nodesize];
    nodesize++;
    return 1;
}
int merge_int(FILE *fp, int l, int r) {
	initHash();
	int ret = 0, x, n = 0;
	fseek(fp, 0, SEEK_SET);
	while ((n = fread(A, sizeof(int), MAXELE, fp))) {
		for (int i = 0; i < n; i++) {
			if (A[i] >= l && A[i] <= r) {
				if (!insertHash(A[i]))
					return 0;
			}
		}
	}
	return 1;
}
#ifdef _WIN32
#include <fcntl.h>
#endif
int block_process(int *base, FILE *fp) {
	int l, r, mid, ret;
	l = *base, r = 1000000000, ret = 0;
#ifdef _WIN32
	if (setmode(fileno(stdout), O_BINARY) == -1) {
		perror("Cannot set stdout to binary mode");
		return 2;
    }
#endif
#ifdef __linux__
	FILE *const out = fdopen(dup(fileno(stdout)), "wb");
#endif
	while (l <= r) {
		mid = (l + r)/2;
		int status = merge_int(fp, *base, mid);
		if (status == 1) {
			l = mid + 1, r = 1000000000;
			*base = mid + 1;
			qsort(hnodes, nodesize, sizeof(HashNode), cmp);
			for (int i = 0; i < nodesize; i++) {
				int x = hnodes[i].f;
				for (int j = hnodes[i].cnt-1; j >= 0; j--) {
#ifdef _WIN32
					fwrite(&x, sizeof(int), 1, stdout);
#endif
#ifdef __linux__
					fwrite(&x, sizeof(int), 1, out);
#endif
				}
				ret += hnodes[i].cnt;
			}
		} else {
			r = mid - 1;
		}
	}
	return ret;
}
int main() {
	char fName[128];
	scanf("%s", fName);
	FILE *fin = fopen(fName, "rb");
	
	int n = fsize(fin) / sizeof(int);
	
	int l = 0, complete = 0;
	while (complete < n) {
		int cnt = block_process(&l, fin);
		complete += cnt;
	}
	return 0;
}
