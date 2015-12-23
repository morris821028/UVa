#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define swap(x, y) {int t; t = x, x = y, y = t;}
int fsize(FILE *fp) {
	int prev = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, prev, SEEK_SET);
	return size;
}
int cmp(const void *x, const void *y) {
	return *(int *) x - *(int *) y;
}
#define USAGEMEM (1<<20)
#define MAXELE ((1<<20)/4)
int A[MAXELE];
int countLess(FILE *fp, int ans) {
	int ret = 0, x, n = 0;
	fseek(fp, 0, SEEK_SET);
	while ((n = fread(A, sizeof(int), MAXELE, fp))) {
		for (int i = 0; i < n; i++)
			ret += A[i] <= ans;
	}
	return ret;
}

int* partition(FILE *fp, int n) {
	fseek(fp, 0, SEEK_SET);
	char tName[128];
	int PARTN = n / MAXELE + (n % MAXELE != 0);
	int *Asize = (int *) malloc(sizeof(int)*PARTN);
	for (int i = 0; i < PARTN; i++) {
		Asize[i] = fread(A, sizeof(int), MAXELE, fp);
		qsort(A, Asize[i], sizeof(int), cmp);
		sprintf(tName, "tmp%d.bin", i);
		FILE *fout = fopen(tName, "wb");
		fwrite(A, sizeof(int), Asize[i], fout);
		fclose(fout);
	}
	return Asize;
}
void merge(int n, int *Asize) {
	char tName[128];
	int PARTN = n / MAXELE + (n % MAXELE != 0);
	int MAXLOAD = MAXELE / PARTN;
	int *fbase = (int *) malloc(sizeof(int)*PARTN);
	int *index = (int *) malloc(sizeof(int)*PARTN);
	int *lsize = (int *) malloc(sizeof(int)*PARTN);
	
	for (int i = 0; i < PARTN; i++)
		fbase[i] = index[i] = lsize[i] = 0;
		
	for (int it = 0; it < n; ) {
		// load data
		for (int i = 0; i < PARTN; i++) {
			if (fbase[i] >= Asize[i]*4)
				continue;
			if (index[i] == lsize[i]) {
				sprintf(tName, "tmp%d.bin", i);
				FILE *tin = fopen(tName, "rb");
				fseek(tin, fbase[i], SEEK_SET);
				lsize[i] = fread(A + i*MAXLOAD, sizeof(int), MAXLOAD, tin);
				index[i] = 0;
				fbase[i] += lsize[i]*4;
				fclose(tin);
			}
		}
		// merge sort
		int mnqid1 = 0, mnval1 = INT_MAX;
		int mnqid2 = 0, mnval2 = INT_MAX;
		for (int i = 0; i < PARTN; i++) {
			if (fbase[i] >= Asize[i]*4 && index[i] == lsize[i])
				continue;
			if (A[i*MAXLOAD + index[i]] < mnval2) {
				mnval2 = A[i * MAXLOAD + index[i]];
				mnqid2 = i;
			}
			if (mnval2 < mnval1) {
				swap(mnval1, mnval2);
				swap(mnqid1, mnqid2);
			}
		}
		
		int wcount = 0;
		while (index[mnqid1] + wcount < lsize[mnqid1] && 
				A[mnqid1*MAXLOAD + index[mnqid1] + wcount] <= mnval2) {
			wcount++;
		}
		fwrite(&A[mnqid1*MAXLOAD + index[mnqid1]], sizeof(int), wcount, stdout);
		it += wcount, index[mnqid1] += wcount;
	}
	return ;
}

int main() {
	char fName[128];
	scanf("%s", fName);
	FILE *fin = fopen(fName, "rb");
	
	int n = fsize(fin) / sizeof(int);
	
	int *Asize = partition(fin, n);
	merge(n, Asize);
	
	return 0;
}
