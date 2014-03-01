#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
char frag[256][512];
int flen[256];
char file[1024];
int main() {
    int t, i, j, p, q;
    scanf("%d", &t);
    while(getchar() != '\n');
    while(getchar() != '\n');
    while(t--) {
        int n = 0;
        int mxlen = 0, mnlen = 0xffff;
        while(gets(frag[n]) && frag[n][0]) {
            flen[n] = strlen(frag[n]);
            if(flen[n] > mxlen)
                mxlen = flen[n];
            if(flen[n] < mnlen)
                mnlen = flen[n];
            n++;
        }
        int file_len = mxlen+mnlen;
        for(i = 0; i < n; i++) {
            if(flen[i] == mxlen || flen[i] == mxlen)
            for(j = 0; j < n; j++) {
                if(flen[i]+flen[j] == file_len) {
                    sprintf(file, "%s%s", frag[i], frag[j]);
                    string A(file), B;
                    for(p = 0; p < n; p++) {
                        int ok = 0;
                        for(q = 0; q < n && !ok; q++) {
                            if(flen[p]+flen[q] == file_len) {
                                B = frag[p];
                                B = B + frag[q];
                                if(A == B)  ok = 1;
                                B = frag[q];
                                B = B + frag[p];
                                if(A == B)  ok = 1;
                            }
                        }
                        if(!ok) break;
                    }
                    if(p == n) {
                        i = n+1, j = n+1;
                        puts(file);
                    }
                }
            }
        }
        if(t)
            puts("");
    }
    return 0;
}
