#include<stdio.h>
long long gcd(long long x, long long y) {
	long long tmp;
	while(x%y) {
		tmp = x, x = y, y = tmp % y;
	} 
	return y;
}
long long ER[1001][1001], EL[1001][1001];
int main() {
	int H, E, i, j, k, l, m;
	int Ele[1001] = {0};
	while(scanf("%d %d", &H, &E) == 2) {
		long long sum = 0, cost;
		long long DP[21][1001] = {0}, min;
		for(i = 1; i <= H; i++)
			scanf("%d", &Ele[i]), sum += Ele[i];
		if(sum == 0 || E >= H)	{puts("0");continue;}
		for(i = 1; i <= H; i++) {
			long long tmpsum = 0;
			for(j = i; j <= H; j++) {
				tmpsum += (j-i)*Ele[j];
				ER[i][j] = tmpsum;
			}
		}
		for(i = 1; i <= H; i++) {
			long long tmpsum = 0;
			for(j = i; j >= 1; j--) {
				tmpsum += (i-j)*Ele[j];
				EL[i][j] = tmpsum;
			}
		}
		for(i = 1; i <= E; i++) { /*i台*/
			for(j = 1; j <= H; j++) {/*j位置*/ 
				min = 0xffffffff;
				for(k = 0; k < j; k++) {/*i-1台 k 位置*/
					if(i == 1 && k > 0)	break;
					if(i > 1 && k == 0)	continue;
					cost = DP[i-1][k];
					if(i > 1) {
/*						for(l = k; l <= H; l++)
							cost -= abs(l-k)*Ele[l];*/
						cost -= ER[k][H];
					}
					m = (k+j)/2;
					if(i == 1)	m = 0;
					cost += ER[k][m];
					cost += EL[j][m+1];
					cost += ER[j][H];
/*					for(l = k; l <= m; l++)
						cost += abs(l-k)*Ele[l];
					for(l = m+1; l <= H; l++)
						cost += abs(l-j)*Ele[l];
						*/
					if(cost < min)	min = cost;
				}
				DP[i][j] = min;
			} 
		}
		min = 0xffffffff;
		for(i = 1; i <= H; i++)
			if(min > DP[E][i])
				min = DP[E][i];
		long long	x = min, y = sum, Gcd = gcd(x, y);
		x /= Gcd, y /= Gcd;
		if(y == 1)
			printf("%lld\n", x);
		else
			printf("%lld/%lld\n", x, y);
	}
    return 0;
}
