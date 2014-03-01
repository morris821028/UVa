#include<stdio.h>
#include<math.h>
void mult(int x[], int y[], int *lx, int *ly) {
	int a, b, t[510] = {}; 
	for(a = 0; a <= *lx; a++) 
		for(b = 0; b <= *ly && a + b <= 500; b++) 
			t[a+b] += (x[a]*y[b]), t[a + b + 1] += t[a+b]/10, t[a+b]%=10;
	int l = ((*lx) + (*ly) + 1 > 500) ? 500 : (*lx)+(*ly)+1;
	while(t[l] == 0) l--;
	for(a = 0; a <= l; a++) 
		x[a] = t[a]; 
	*lx = l; 
} 
void ans(int P) {
	int t = (int)(P * log10(2)) + 1, a; 
	int x[510] = {1}, y[510] = {2}, lx = 0, ly = 0;
	printf("%d", t); 
	while(P) {
		if(P&1) {
			mult(x, y, &lx, &ly); 
		}
		mult(y, y, &ly, &ly), P /= 2; 
	} 
	x[0]--; 
	for(a = 499; a>=0; a--) { 
		if((a+1) % 50 == 0)  puts(""); 
		printf("%d", x[a]); 
	} 
	puts(""); 
} 
main() {
	int P; 
	while(scanf("%d", &P) == 1) {
		ans(P); 
	}
	return 0; 
}
