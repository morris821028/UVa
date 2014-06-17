#include <stdio.h>

int main() {
    char s[1024];
    int i, j;
    while(gets(s)) {
        printf("Expression: %s\n", s);
        int val[26];
        int pos_val[26] = {}, used[26] = {};
        int pre_val = -1;
        for(i = 0; i < 26; i++)
            val[i] = i+1;
        for(i = 0, j = 0; s[i]; i++)
            if(s[i] != ' ')
                s[j++] = s[i];
        s[j] = s[j+1] = s[j+2] = '\0';
        for(i = 0; s[i]; i++) {
            if(s[i] >= 'a' && s[i] <= 'z') { // [a-z]
                used[s[i]-'a'] = 1;
                if(s[i+1] == '+' && s[i+2] == '+') { // i++
                    pos_val[s[i]-'a']++;
                    s[i+1] = s[i+2] = ' ', i += 2;
                } else if(s[i+1] == '-' && s[i+2] == '-') { // i--
                    pos_val[s[i]-'a']--;
                    s[i+1] = s[i+2] = ' ', i += 2;
                } else if(i-2 >= 0 && s[i-1] == '+' && s[i-2] == '+') { // ++i
                    val[s[i]-'a']++;
                    s[i-1] = s[i-2] = ' ';
                } else if(i-2 >= 0 && s[i-1] == '-' && s[i-2] == '-') { // --i
                    val[s[i]-'a']--;
                    s[i-1] = s[i-2] = ' ';
                }
            }
        }
        int plus = 1, value = 0;
        for(i = 0; s[i]; i++) {
            if(plus && s[i] >= 'a' && s[i] <= 'z')
                value += val[s[i]-'a'];
            if(!plus && s[i] >= 'a' && s[i] <= 'z')
                value -= val[s[i]-'a'];
            if(s[i] == '+') plus = 1;
            if(s[i] == '-') plus = 0;
        }
        printf("    value = %d\n", value);
        for(i = 0; i < 26; i++) {
            if(used[i]) {
                printf("    %c = %d\n", i+'a', val[i]+pos_val[i]);
            }
        }
    }
    return 0;
}
