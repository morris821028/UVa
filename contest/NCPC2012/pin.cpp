#include <stdio.h>
#include <stdlib.h>
#include <time.h>
main() {
	int n, m, t, a, b, c, tmp;
	int x, y, z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);
	t = 19;
	printf("%d\n", t), i=2;
	while(t--) {
	    printf("%d %d\n", i, rand()%100+1);
	    i++;
	}
	/*
	t = 20;
	printf("%d\n", t);
	while(t--) {
	    y = rand()%500+1, i = rand()%50+1, z = rand()%100+1;
	    printf("%d %d %d\n", y, i, z);
	}*/
	/*
	for(i = 0; i < 50; i++) {
	    n = 30, m = rand()%200+1;
	    printf("%d\n", m);
	    int toy[n];
	    for(j = 0; j < n; j++) {
	        while(1) {
	            x = rand()%10000;
	            for(k = 0; k < j; k++) {
	                if(toy[k] == x)
                        break;
	            }
	            if(k == j) {
	                toy[j] = x;
	                break;
	            }
	        }
	    }
	    for(j = 0; j < m; j++) {
	        x = toy[rand()%n];
	        while(1) {
	            y = toy[rand()%n];
	            if(x != y)  break;
	        }
	        printf("%d %d\n", x, y);
	    }
	}
	for(i = 0; i < 4; i++) {
	    if(i < 2)   n = 10, m = 5000;
	    else        n = 100, m = 50;
	    printf("%d\n", m);
	    int toy[n];
	    for(j = 0; j < n; j++) {
	        while(1) {
	            x = rand()%10000;
	            for(k = 0; k < j; k++) {
	                if(toy[k] == x)
                        break;
	            }
	            if(k == j) {
	                toy[j] = x;
	                break;
	            }
	        }
	    }
	    for(j = 0; j < m; j++) {
	        x = toy[rand()%n];
	        while(1) {
	            y = toy[rand()%n];
	            if(x != y)  break;
	        }
	        printf("%d %d\n", x, y);
	    }
	}
	for(i = 0; i < 4; i++) {
	    if(i < 2)   n = 15,m = 400;
	    else        n = 250, m = 30;
	    printf("%d\n", m);
	    int toy[n];
	    for(j = 0; j < n; j++) {
	        while(1) {
	            x = rand()%10000;
	            for(k = 0; k < j; k++) {
	                if(toy[k] == x)
                        break;
	            }
	            if(k == j) {
	                toy[j] = x;
	                break;
	            }
	        }
	    }
	    for(j = 0; j < m; j++) {
	        x = toy[rand()%n];
	        while(1) {
	            y = toy[rand()%n];
	            if(x != y)  break;
	        }
	        printf("%d %d\n", x, y);
	    }
	}
	puts("0");*/
/*
	t = 100;
	printf("%4d\n", t);
	while(t--) {
	    n = rand()%1+2;
	    printf("%4d\n", n);
	    int M[3][3];
	    while(1) {
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    M[i][j] = rand()%11;
            int det;
            if(n == 2) {
                det = M[0][0]*M[1][1] - M[0][1]*M[1][0];
            } else {
                det = M[0][0]*M[1][1]*M[2][2] + M[0][1]*M[1][2]*M[2][0] + M[0][2]*M[1][0]*M[2][1]-
                        M[0][2]*M[1][1]*M[2][0] - M[1][2]*M[2][1]*M[0][0] - M[0][1]*M[1][0]*M[2][2];
            }
            if(det%11)  break;
	    }
	    for(i = 0; i < n; i++, puts(""))
            for(j = 0; j < n; j++)
                printf("%4d", M[i][j]);
	    for(i = 0; i < 12; i++) {
	        int tmp = rand()%11;
	        if(tmp == 10)   printf(":");
	        else printf("%d", tmp);
	    }
	    puts("");
	}*/
	/*
	char buf[100], bt = 0;
    for(i = '0'; i <= '9'; i++) buf[bt++] = i;
    for(i = 'A'; i <= 'Z'; i++) buf[bt++] = i;
    for(i = 'a'; i <= 'z'; i++) buf[bt++] = i;
	for(i = 0; i < 600; i++) {
        for(j = 0; j < 5; j++) {
            printf("%c", buf[rand()%bt]);
        }
        puts("");
    }*/
	return 0;
}
