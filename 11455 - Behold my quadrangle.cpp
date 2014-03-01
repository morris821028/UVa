#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int t, e[4], i;
    scanf("%d", &t);
    while(t--) {
        for(i = 0; i < 4; i++)
            scanf("%d", e+i);
        sort(e, e+4);
        if(e[0] == e[3])
            puts("square");
        else if(e[0] == e[1] && e[2] == e[3])
            puts("rectangle");
        else if(e[3] <= e[0]+e[1]+e[2])
            puts("quadrangle");
        else
            puts("banana");
    }
    return 0;
}
