#include <stdio.h> 
#include <math.h>
using namespace std;
double q[1000005], p;
int np[1000005];
int main() {
	q[0] = 1, np[0] = 0;
	double r = 1;
	for(long long i = 1; i < 1000005; i++) {
		p = 1.0 / (i * (i+1));
		q[i] = q[i-1] * (1 - p);
		r *= p;
		np[i] = np[i-1];
		while(r < 1) {
			r *= 10;
			np[i]++;
		}
	}
	int n;
	while(scanf("%d", &n) == 1) {
		printf("%lf %d\n", 1 - q[n], np[n]-1);
	}
	return 0;
}
