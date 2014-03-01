#include<stdio.h>
#include<math.h>
#include<string.h>
int mark[1000000], Q[1000000], Qt;
int F[1000001];
struct state{
	int tail, cycle, start;
}K[1001];
int POW(unsigned long long x, unsigned long long y, int mod) {
	int Ans = 1, t = x%mod;
	while(y) {
		if(y&1) {
			Ans *= t%mod, Ans %= mod;
		}
		t *= t%mod, t %= mod;
		y = y/2;
	}
	return Ans;
}
int Build() {
	int k, i, total = 0, t, tail, cycle;
	memset(mark, -1, sizeof(mark));
	for(k = 1; k <= 1000; k++) {
		K[k].start = total, Qt = 0;
		for(i = 0; ; i++) {
			if(i < 2)	F[i+total] = i%k;
			else		F[i+total] = (F[i-1+total] + F[i-2+total])%k;
			t = F[i+total];
			if(i >= 1)	t += F[i-1+total]*1000;
			if(mark[t] != -1) {
				tail = mark[t], cycle = i - tail;
				break;
			}
			mark[t] = i;
			Q[Qt++] = t;
		}
		tail--;
		K[k].tail = tail, K[k].cycle = cycle;
		total += i;
		for(i = 0; i < Qt; i++)
			mark[Q[i]] = -1;
	}
}
main() {
	Build();
	int n, i, j, T;
	unsigned long long a, b;
	scanf("%d", &T);
	while(T--) {
		scanf("%llu %llu %d", &a, &b, &n);
		int tail, cycle, start;
		tail = K[n].tail, cycle = K[n].cycle, start = K[n].start;
		int Ans;
		if(b*log10(a) <= log10(tail))
			Ans = F[(int)(pow(a, b))+start];
		else {
			int tmp;
			tmp = POW(a, b, cycle);
			if(tmp == 0)	tmp += cycle;
			tmp = ((tmp - tail)%cycle+cycle)%cycle + tail;
			Ans = F[tmp+start];
		}
		printf("%d\n", Ans);
	}
	return 0;
}
