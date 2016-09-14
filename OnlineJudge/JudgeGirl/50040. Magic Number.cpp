#include <stdio.h>
 
int main() {
    int M;
    scanf("%d", &M);
    printf("%d\n", M > 0 && M % 2 == 0 && (M > 10000 || M < 1000));
    return 0;
}

