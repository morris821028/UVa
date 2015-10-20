#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int testcase = 1;
    while (testcase--) {
    	int n = 20;
    	printf("%d\n", 2*n-1);
    	int prev = 1;
    	for (int i = 0; i < n; i++) {
    		if (prev == 4)
    			printf("%d ", rand()%10+1);
    		else	
    			printf("%d ", rand()%10 - 5);
    		int op;
			while (true) {
				op = rand()%4+1;
				if (prev >= 3 && op >= 3)
					continue;
    			printf("%d ", op);
    			break;
    		}
    		prev = op;
    	}
    	puts("");
	}
    return 0;
}
