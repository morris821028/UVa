#include <stdio.h> 
 
int main() {
    int n;
    int ret = 0;
    int h1, h2, h3;
    scanf("%d", &n);
    scanf("%d %d", &h1, &h2);
    ret = h2 > h1 ? 3 * (h2 - h1) : 2 * (h1 - h2);
    for (int i = 2; i < n; i++) {
        scanf("%d", &h3);
        if (h3 > h2) {
            ret += h2 > h1 ? 4 * (h3 - h2) : 3 * (h3 - h2);
        } else {
            ret += h2 > h1 ? 3 * (h2 - h3) : 2 * (h2 - h3);
        }
        h1 = h2, h2 = h3;
    }
    printf("%d\n", ret);
    return 0;
}

