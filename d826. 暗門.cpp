

#include<stdio.h>
#include<stdlib.h>
int Input() {  
    char cha;  
    unsigned int x = 0;  
    while(cha = getchar())  
        if(cha != ' ' && cha != '\n' || cha == EOF) break;  
    if(cha == EOF) return -1; 
    x = cha-48;  
    while(cha = getchar()) {  
        if(cha == ' ' || cha == '\n') break;  
        x = x*10 + cha-48;  
    }  
    return x;  
}	
main() {
	int n = 5, m =250 , x;
	while(scanf("%d %d", &n, &m) == 2) {
		int a, room[100002] = {0}, U = 1, Ans = 0;
		for(a = 0; a < m; a++) {
			x = Input(), room[x]++;
		}
		m /= n;
		for(a = 1; a <= n; a++) {
			while(room[a] > m) {
				while(room[U] >= m)	U++;
				if(room[a] - m >= m - room[U]) 
					Ans += (m-room[U])*abs(U-a), room[a]-= m-room[U], room[U] = m;
				else 
					Ans += (room[a]-m)*abs(U-a), room[U]+= room[a]-m, room[a] = m;
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}
