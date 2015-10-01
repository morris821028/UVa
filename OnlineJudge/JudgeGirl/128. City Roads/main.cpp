#include <stdio.h>
#include "intersection.h"  
 
int main() { 
	int g[100][100], n;
    while (scanf("%d", &n) == 1) { 
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                scanf("%d", &g[i][j]); 
        int ret[4];
        intersection(g, ret);
        for (int i = 0; i < 4; i++)
        	printf("%d\n", ret[i]);
    } 
    return 0; 
} 
