#include <stdio.h>
using namespace std;

int main() {
    int P, H, O;
    while (scanf("%d %d %d", &P, &H, &O) == 3) {
        if (H > O - P)
            puts("Hunters win!");
        else
            puts("Props win!");
    }
    return 0;
}
/*

*/