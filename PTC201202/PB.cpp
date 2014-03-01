#include<stdio.h>
#include<stdlib.h>
int main() {
	int n, a, b, c, d;
	while(scanf("%d",&n) == 1 && n) {
		while(1) {
	    	int stack[1001]={0}, mark[1001], flag=1;
    		if(scanf("%d",&mark[1]));
	    	if(mark[1] == 0)	  	break;
    		for(a = 1; a <= n; a++)
		  		stack[a] = a;
		    for(a = 2 ; a <= n; a++) 
				scanf("%d", &mark[a]);
        	for(a = 1, b = 0; a <= n && flag != 0; a++) {
	    		c = mark[a];
	        	if(b < c) {
            		b = c;
		            stack[c] = 0;
    		    } else {
        	    	for(d = b-1; d > c; d--)
            	  		if(stack[d]) {
                			flag = 0;
		              		break;
        			    }
		        	stack[c]=0;
        		}
       		}
			if(flag == 1)
    			printf("Yes\n");
	       else
    		    printf("No\n");
	    }
		puts("");
	}
	return 0;
}
