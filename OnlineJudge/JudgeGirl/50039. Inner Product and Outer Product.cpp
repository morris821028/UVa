#include <stdio.h>
 
int main() {
    int ax, ay, az, bx, by, bz;
    scanf("%d%d%d", &ax, &ay, &az);
    scanf("%d%d%d", &bx, &by, &bz);
    printf("%d\n", ax*bx+ay*by+az*bz);
    printf("%d %d %d\n", ay*bz-az*by, az*bx-ax*bz, ax*by-ay*bx);
    return 0;
}

