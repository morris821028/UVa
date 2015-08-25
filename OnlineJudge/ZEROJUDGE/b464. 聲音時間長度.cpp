#include <bits/stdc++.h> 
using namespace std;

int main() {
	int R, N;
	scanf("%d %d", &R, &N);
//	for (int i = 0; i < N; i++)
//		scanf("%*d");
	int ff = round((double)N / R);
	printf("%d:%02d\n", ff/60, ff%60);
	return 0;
}
