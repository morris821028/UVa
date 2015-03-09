#include<stdio.h>         
#include<stdlib.h>
inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline double ReadPoint() {
    static char c;
    int p = 0;
    double t = 1;
    while((c = readchar()) >= '0')
        t /= 10, p = (p << 3) + (p << 1) + (c-'0');
    return (double)p*t;
}
inline int ReadDouble(double *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return EOF;}
    if(c == '.')    {*x = ReadPoint();return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x)*10 + c-'0';
    if(c == '.')    *x += ReadPoint();
    *x *= neg;
    return 0;
}  
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
main() {
	int t, n, maxflag;      
	double sum, max, m;
	while(ReadInt(&t) != EOF) {
		int a, b, c, flag;      
		while(t--) {
			ReadInt(&n);
     		flag = 1;
			int x[1000] = {0};
			for(a = 0; a < n; a++) {
				sum = 0, max = -1;
				for(b = 0; b < n; b++)  {
		    		ReadDouble(&m);
         			if(m < 0) m *= -1;   
					sum += m;
					if(m > max)
						max = m, maxflag = b;
	        	}
				sum -= max;
				if(sum >= max) flag = 0;
				if(flag) {
					if(x[maxflag]) flag = 0;
					else x[maxflag] = 1;
				}
      		}
    		puts(flag ? "yes" : "no");
		}
	}
	return 0; 
}
