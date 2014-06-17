#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
    int n, m;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        double longest = 0, V, tmp;
        int p = 0, i;
		char s1[100], s2[100];
        for(i = 1; i <= n; i++) {
            V = (double)n/i;
            if(V-m > 0)
               tmp = 0.3*sqrt(V-m)*i;
            else {
               break;
			}
            sprintf(s1, "%.10lf", tmp);
            sprintf(s2, "%.10lf", longest);
            if(strcmp(s1, s2) == 0)
                p = 0;
            else if(tmp > longest)
                p = i, longest = tmp;
            else if(tmp < longest)
            	break;
        }
        printf("%d\n", p);
    }
    return 0;
}
