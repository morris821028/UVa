#include <stdio.h>

int fsize(FILE *fp) {
	int prev = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, prev, SEEK_SET);
	return size;
}

#define USAGEMEM (2<<20)
#define MAXELE (2<<20)/4
int countLess(FILE *fp, int ans) {
	static int A[MAXELE];
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
	
	while (l <= r) {
		mid = (l + r)/2;
		int tn = countLess(fin, mid);
		if (tn < m)
			l = mid + 1, ret = mid+1;
		else
			r = mid - 1;
	}
	printf("%d\n", ret);
	return 0;
}
