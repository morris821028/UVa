#include <stdio.h>
#include <string.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        char s[50];
        getchar();
        int i, j, shift = 0xfffff;
        int a[50], left, right;
        for(i = 0; i < n; i++) {
            gets(s);
            j = 0;
            while(s[j] != '\0' && s[j] == 'X')
                j++;
            left = j;
            while(s[j] != '\0' && s[j] != 'X')
                j++;
            right = j;
            a[i] = right - left;
            if(a[i] < shift)
                shift = a[i];
        }
        int sum = 0;
        for(i = 0; i < n; i++)
            sum += a[i]-shift;
        printf("%d\n", sum);
    }
    return 0;
}
