#include<stdio.h>
int Prime[100], Pt;
void Sieve() {
	Pt = 0;
	int i, j, mark[100] = {0};
	Prime[Pt++] = 2;
	for(i = 3; i < 100; i += 2) {
		if(mark[i] == 0) {
			Prime[Pt++] = i;
			for(j = 3; i*j < 100; j += 2)
				mark[i*j] = 1;
		}
	}
}
void solve(int n) {
	int table[100] = {0}, i, j, tmp;
	for(i = 2; i <= n; i++) {
		tmp = i;
		for(j = 0; j < Pt && tmp != 1; j++)
			while(tmp%Prime[j] == 0)
				tmp /= Prime[j], table[j]++;
	}
	printf("%3d! =", n);
	int length = Pt, count = 0;
	while(table[length] == 0)	length--;
	for(i = 0; i <= length; i++) {
		count++;
		if(count > 15)	count -= 15, printf("\n      ");
		printf("%3d", table[i]);
	}
	puts("");
}
int main() {
	Sieve();
	int N;
	while(scanf("%d", &N) == 1 && N) {
		solve(N);
	}
    return 0;
}
