#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
    int A, B, C, X, Y;
    while(scanf("%d %d %d %d %d", &A, &B, &C, &X, &Y) == 5) {
        if(A == 0)  break;

        int used[60] = {};
        used[A] = used[B] = used[C] = used[X] = used[Y] = 1;
        int found = 0, i, j;
        for(i = 1; i <= 52; i++) {
            if(used[i])    continue;
            int arr[3] = {X, Y, i}, w = 0;
            if(arr[0] > A)  w++;
            if(arr[1] > B)  w++;
            if(arr[2] > C)  w++;
            if(w < 2) continue;
            w = 0;
            if(arr[0] > A)  w++;
            if(arr[2] > B)  w++;
            if(arr[1] > C)  w++;
            if(w < 2) continue;
            w = 0;
            if(arr[1] > A)  w++;
            if(arr[0] > B)  w++;
            if(arr[2] > C)  w++;
            if(w < 2) continue;
            w = 0;
            if(arr[1] > A)  w++;
            if(arr[2] > B)  w++;
            if(arr[0] > C)  w++;
            if(w < 2) continue;
            w = 0;
            if(arr[2] > A)  w++;
            if(arr[0] > B)  w++;
            if(arr[1] > C)  w++;
            if(w < 2) continue;
            w = 0;
            if(arr[2] > A)  w++;
            if(arr[1] > B)  w++;
            if(arr[0] > C)  w++;
            if(w < 2) continue;
            found = 1;
            printf("%d\n", i);
            break;
        }
        if(!found)  puts("-1");
    }
    return 0;
}
