#include <stdio.h>
char var[] = "abcdefgh", order[10] = "a";
char space[10][30] = {
    "", "  ", "    ", "      ", "        ", "        ",
    "          ", "            ", "              ",
    "                " };
void MetaSort(int idx, int n) {
    int i;
    if(idx == n) {
        printf("%swriteln(%c", space[idx], order[n-1]);
        for(i = n-2; i >= 0; i--) {
            putchar(',');
            putchar(order[i]);
        }
        puts(")");
        return;
    }
    printf("%s", space[idx]);
    for(i = idx; i >= 1; i--)
        order[i] = order[i-1];
    for(i = 0; i < idx; i++) {
        printf("if %c < %c then\n", order[i+1], var[idx]);
        order[i] = var[idx];
        MetaSort(idx+1, n);
        order[i] = order[i+1];
        printf("%selse ", space[idx]);
    }
    puts("");
    order[i] = var[idx];
    MetaSort(idx+1, n);
}
int main() {
    int t, n, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        printf("program sort(input,output);\nvar\n");
        putchar('a');
        for(i = 1; i < n; i++) {
            putchar(',');
            putchar(var[i]);
        }
        puts(" : integer;\nbegin");
        printf("  readln(a");
        for(i = 1; i < n; i++) {
            putchar(',');
            putchar(var[i]);
        }
        puts(");");
        MetaSort(1, n);
        puts("end.");
        if(t)
            puts("");
    }
    return 0;
}
