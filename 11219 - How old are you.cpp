#include <stdio.h>

int main() {
    int t, test = 0;
    scanf("%d", &t);
    while(t--) {
        int age, a, b, c, e, f, g;
        scanf("%d/%d/%d", &a, &b, &c);
        scanf("%d/%d/%d", &e, &f, &g);
        age = c-g;
        if(f > b)   age--;
        if(f == b && e > a)   age--;
        printf("Case #%d: ", ++test);
        if(age < 0)
            puts("Invalid birth date");
        else if(age > 130)
            puts("Check birth date");
        else
            printf("%d\n", age);
    }
    return 0;
}
