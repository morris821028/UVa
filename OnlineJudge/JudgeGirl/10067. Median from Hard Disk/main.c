#include <bits/stdc++.h>
using namespace std;

#define MAXN 1048576
int A[MAXN];

int main() {
	char fName[128];
	scanf("%s", fName);
	FILE *fin = fopen(fName, "rb");
	
	int n = fread(A, sizeof(int), MAXN, fin);
	
	sort(A, A+n);
	
	printf("%d\n", A[n/2]);
	return 0;
}

