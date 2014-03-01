#include <stdio.h>
char s;
char stack[1000000];
int main() {
    int idx = 0;
    while(s = getchar()) {
        if(s == EOF)
            break;
            switch(s) {
                case 'a' ... 'z':
                    stack[idx++] = s;
                    break;
                case 'A' ... 'Z':
                    stack[idx++] = s;
                    break;
                default:
                    if(idx > 0) {
                        stack[idx] = '\0';
                        switch(stack[0]) {
                            case 'a':
                            case 'e':
                            case 'i':
                            case 'o':
                            case 'u':
                            case 'A':
                            case 'E':
                            case 'I':
                            case 'O':
                            case 'U':
                                printf("%say", stack);
                                break;
                            default:
                                printf("%s%cay", stack+1, stack[0]);
                        }
                        idx = 0;
                    }
                    putchar(s);
            }
    }
    return 0;
}
