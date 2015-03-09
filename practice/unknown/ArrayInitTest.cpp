#include <stdio.h>
int gobel_1[2][2];
int gobel_2[2][2] = {};
int gobel_3[2][2] = {0};
void print(int a[][2]) {
    int i, j;
    for(i = 0; i < 2; i++) {
        putchar('[');
        for(j = 0; j < 2; j++)
            printf("%d ", a[i][j]);
        puts("]");
    }
}
int main() {
    int local_1[2][2];
    int local_2[2][2] = {};
    int local_3[2][2] = {0};
    print(gobel_1);
    print(gobel_2);
    print(gobel_3);
    print(local_1);
    print(local_2);
    print(local_3);
    return 0;
}
