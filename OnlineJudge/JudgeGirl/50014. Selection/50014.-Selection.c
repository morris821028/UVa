#include "subset.h"
#include <stdio.h>
int subset(int numbers[], int n, int K, int S){
    if(K<0 || S>n || (K==0 && S>0))
        return 0;
    if(S==1 && K==*numbers)
        return 1;
    if (S == 0)
    	return 0;
    else if(n!=1)
        return (subset(numbers+1,n-1,K-*numbers,S-1) || subset(numbers+1,n-1,K,S));
    return 0;
}
