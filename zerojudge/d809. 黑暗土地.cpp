#include<stdio.h>
#include<stdlib.h> 
struct D{
	int x, y; 
}s[200]; 
main() {
	int N, a, b, c;
	while(scanf("%d", &N) == 1) {
		for(a = 0; a < N; a++)
			scanf("%d %d", &s[a].x, &s[a].y); 
		int max = 0, t;
		for(a = 0; a < N; a++) 
			for(b = a+1; b < N; b++) 
				for(c = b+1; c < N; c++) {
					t =  abs(s[a].x*s[b].y + s[b].x*s[c].y + s[c].x*s[a].y
							-s[a].y*s[b].x - s[b].y*s[c].x - s[c].y*s[a].x 
						);
					if(t > max) max = t; 
				} 
		printf("%.2lf\n", max / 2.0); 
	} 
	return 0; 
}
