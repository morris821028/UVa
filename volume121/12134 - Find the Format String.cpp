#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int main() {
    int n, cases = 0;
    char in[128][128], out[128][128];
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++)
            scanf("%s %s", in[i], out[i]);
        
        int ascii[128] = {};
        for (int i = '0'; i <= '9'; i++)
            ascii[i] = 1;
        for (int i = 'A'; i <= 'Z'; i++)
            ascii[i] = 1;
        for (int i = 'a'; i <= 'z'; i++)
            ascii[i] = 1;
        
        for (int i = 0; i < n; i++) {
            for (int j = 1; out[i][j]; j++) {
                if (in[i][j] != out[i][j]) {
                    ascii[in[i][j]] = 0;
                } else {
                    if (ascii[in[i][j]]) {
                        ascii[in[i][j]] |= 2;
                    }
                }
            }
        }
        
        char ret[128];
        int m = 0;
        for (int i = '0', j = '0' - 1; i < 128; i++) {
//            printf("%d %d\n", i, ascii[i]);
            if (ascii[i] == 3) {
                while (j < i) {
                    if (ascii[j] == 1)
                        ret[m++] = j;
                    j++;
                }
                ret[m++] = i;
            }
        }
        if (m == 0) {
            for (int i = '0'; i < 128; i++) {
                if (ascii[i] == 1) {
                    ret[m++] = i;
                    break;
                }
            }
        }
        ret[m] = '\0';
        char format[128];
        format[0] = '%', format[1] = '[';
        for (int i = 0; i < m; i++)
            format[i+2] = ret[i];
        format[m+2] = ']', format[m+3] = '\0';
        int ok = 1;
        if (m == 0)
            ok = 0;
        for (int i = 0; i < n && ok; i++) {
            char s[128] = {};
            in[i][strlen(in[i]) - 1] = '\0';
            sscanf(in[i]+1, format, s + 1);
            s[0] = '"';
            int len = (int)strlen(s);
            s[len] = '"', s[len+1] = '\0';
            ok &= !strcmp(s, out[i]);
        }
        printf("Case %d: %s\n", ++cases, ok ? format+1 : "I_AM_UNDONE");
    }
    return 0;
}

/*
 5
 "11" "11"
 "243" "24"
 "563" "56"
 "784" "784"
 "789" "78"
 1
 "A" "b" 
 0
 */
