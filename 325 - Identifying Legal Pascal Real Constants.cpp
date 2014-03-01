#include <stdio.h>
#include <string.h>
int main() {
    char s[1000];
    while(gets(s)) {
        if(!strcmp(s, "*"))
            break;
        int i = 0, j = strlen(s)-1;
        while(s[i] == ' ')  i++;
        while(s[j] == ' ')  j--;
        char trim[1000];
        memcpy(trim, s+i, j-i+1);
        trim[j-i+1] = '\0';
        int len = strlen(trim);
        int error = 0;
        i = 0;
        if(trim[i] == '+' || trim[i] == '-')
            i++;
        j = i;
        while(trim[i] >= '0' && trim[i] <= '9' && i < len)
            i++;
        if(j == i)  error = 1;
        if(i < len && trim[i] == '.') {
            i++;
            j = i;
            while(trim[i] >= '0' && trim[i] <= '9' && i < len)
                i++;
            if(j == i)  error = 1;
            if(i < len && (trim[i] == 'e' || trim[i] == 'E')) {
                i++;
                if(trim[i] == '+' || trim[i] == '-')
                    i++;
                j = i;
                while(trim[i] >= '0' && trim[i] <= '9' && i < len)
                    i++;
                if(j == i)  error = 1;
                else if(i < len) {error = 1;}
            } else if(i < len) {error = 1;}
        } else if(i < len && (trim[i] == 'e' || trim[i] == 'E')) {
            i++;
            if(trim[i] == '+' || trim[i] == '-')
                i++;
            j = i;
            while(trim[i] >= '0' && trim[i] <= '9' && i < len)
                i++;
            if(j == i)  error = 1;
            else if(i < len) {error = 1;}
        } else {error = 1;}
        if(error)
            printf("%s is illegal.\n", trim);
        else
            printf("%s is legal.\n", trim);
    }
    return 0;
}
