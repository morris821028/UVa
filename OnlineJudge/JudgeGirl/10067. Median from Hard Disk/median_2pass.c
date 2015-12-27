#include <stdio.h>
#include <assert.h>
#include <string.h>
int fsize(FILE *fp) {
	int prev = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, prev, SEEK_SET);
	return size;
}

#define MAXELE ((1<<20)/4)
static int A[MAXELE];
static int B[MAXELE];
int countLess(FILE *fp, int ans) {
	int ret = 0, x, n = 0;
	fseek(fp, 0, SEEK_SET);
	while ((n = fread(A, sizeof(int), MAXELE, fp))) {
		for (int i = 0; i < n; i++)
			ret += A[i] <= ans;
	}
	return ret;
}

int main() {
	char fName[128];
	scanf("%s", fName);
	FILE *fin = fopen(fName, "rb");
	
	int n = fsize(fin) / sizeof(int);
	
	int m = n/2 + 1;
	int l = 0, r = 1000000000, mid, ret = 0;
	
	int WIDTH = r, SHIFT;
	
	for (SHIFT = 1; (1<<SHIFT) < MAXELE; SHIFT++);
	WIDTH = r / (1<<SHIFT);
	
	memset(B, 0, sizeof(B));
	fseek(fin, 0, SEEK_SET);
	while ((n = fread(A, sizeof(int), MAXELE, fin))) {
		for (int i = 0; i < n; i++) {
			assert((A[i]>>SHIFT) < MAXELE);
			B[A[i]>>SHIFT]++;
		}
	}
	
	int BASE = 0, SELECT;
	for (int i = 0, sum = m; i < MAXELE; i++) {
		sum -= B[i];
		if (sum <= 0) {
			BASE = i * (1<<SHIFT);
			SELECT = sum + B[i];
			break;
		}
	}
	
	memset(B, 0, sizeof(B));
	fseek(fin, 0, SEEK_SET);
	while ((n = fread(A, sizeof(int), MAXELE, fin))) {
		for (int i = 0; i < n; i++) {
			if (A[i] - BASE < MAXELE && A[i] >= BASE)
				B[A[i] - BASE]++;
		}
	}
	for (int i = 0, sum = SELECT; i < MAXELE; i++) {
		sum -= B[i];
		if (sum <= 0) {
			printf("%d\n", i + BASE);
			break;
		}
	}
	return 0;
}



