#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<map>
#define mem(x) memset(x,0,sizeof(x))
using namespace std;

typedef long long ll;

int main(){
    char s[4100];
    while(gets(s)) {
        int len = strlen(s);
        int i, j, k;
        for(i = 0; i < len/16; i++) {
            printf("%04x:", i*16);
            for(j = i*16; j < i*16+16; j+=2) {
                printf(" %02x%02x", s[j], s[j+1]);
            }
            putchar(' ');
            for(j = i*16; j < i*16+16; j++) {
                if(s[j] >= 'A' && s[j] <= 'Z')
                    putchar(s[j]-'A'+'a');
                else if(s[j] >= 'a' && s[j] <= 'z')
                    putchar(s[j]-'a'+'A');
                else
                    putchar(s[j]);
            }
            puts("");
        }
        if(len%16) {
            printf("%04x:", i*16);
            for(j = i*16; j < len; j+=2) {
                printf(" %02x", s[j]);
                if(j+1 < len)
                    printf("%02x", s[j+1]);
                else
                    printf("  ");
            }
            for(; j < i*16+16; j += 2)
                printf("     ");
            putchar(' ');
            for(j = i*16; j < len; j++) {
                if(s[j] >= 'A' && s[j] <= 'Z')
                    putchar(s[j]-'A'+'a');
                else if(s[j] >= 'a' && s[j] <= 'z')
                    putchar(s[j]-'a'+'A');
                else
                    putchar(s[j]);
            }
            puts("");
        }
    }
    return 0;
}
/*
Hex Dump
#include <cstdio>
*/
