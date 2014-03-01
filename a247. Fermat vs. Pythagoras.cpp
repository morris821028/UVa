#include<stdio.h>      
#include<stdlib.h>
#include<string.h> 
#define MaxN 1000000
#define oo 2147483647
int gcd(int x, int y) {
	int tmp;
	while(x%y) {
		tmp = x, x = y, y = tmp%y;
	}
	return y;
}
int mask1[MaxN+1], mask2[MaxN+1], Ans[MaxN+1];
int min(int x, int y) {
	return x < y ? x : y;
}
int Build() {

	int n, m, i, j, k, a, b, c;	
	for(i = 0; i <= MaxN; i++)
		mask1[i] = oo;
	memset(mask2, 0, sizeof(mask2));
	memset(Ans, 0, sizeof(Ans));
	for(i = 1; i < 1000; i++)
		for(j = i+1; j < 1000; j += 2) {
			if(gcd(i, j) > 1)	continue;
			a = j*j - i*i, b = 2*i*j, c = j*j + i*i;
			if(c > MaxN)	break;
			mask2[c]++;
			for(k = 1; k*c <= MaxN; k++) {
				mask1[k*a] = min(k*c, mask1[k*a]);
				mask1[k*b] = min(k*c, mask1[k*b]);
				mask1[k*c] = min(k*c, mask1[k*c]);
			}
		}
	for(i = 1; i <= MaxN; i++)
		if(mask1[i] <= MaxN)
			Ans[mask1[i]]++;
	for(i = 1; i <= MaxN; i++) {
		mask2[i] += mask2[i-1];
		Ans[i] += Ans[i-1];
	}
}
int main() {   
	int N;
	Build();
	while(scanf("%d", &N) == 1&& N)	{
		printf("%d %d\n", mask2[N], N-Ans[N]);
	}   
   return 0;   
}   
/*利用此一性質，計算所有斜邊小於10000000的素勾股數，*/  
/* abc為三邊  m > n 、 m 和 n 均是正整*/  
/*a = m^2 -n^2, */  
/*b = 2mn, */  
/*c = m^2+n^2*/
