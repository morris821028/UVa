#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
    int n, p;
    int i, j;
    int C[150005];
    char A[150005], B[150005];
    while(scanf("%d %d", &n, &p) == 2) {
        if(n == 0)  break;
        scanf("%s %s", A+1, B+1);
        for(i = 1; i <= n; i++)
            C[i] = (A[i] == B[i])*100 - p;
        int sum = 0;
        for(i = 1; i <= n; i++) {
            sum
        }
    }
    return 0;
}
