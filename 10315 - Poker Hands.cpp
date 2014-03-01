#include <stdio.h>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
int s2n(char c) {
    if(c >= '0' && c <= '9')
        return c-'0';
    if(c == 'A')    return 14;
    if(c == 'T')    return 10;
    if(c == 'J')    return 11;
    if(c == 'Q')    return 12;
    if(c == 'K')    return 13;
}
char b[5], w[5], fb[5], fw[5];
int solve() {
    sort(b, b+5), sort(w, w+5);
    sort(fb, fb+5), sort(fw, fw+5);
    int BB = 0, WW = 0;
    int a1, a2, b1, b2, c1, c2, d1, d2;
    // straight flush
    if(fb[0] == fb[4] && b[0]+4 == b[4])
        BB = b[4];
    if(fw[0] == fw[4] && w[0]+4 == w[4])
        WW = w[4];
    //printf("straight flush %d %d\n", BB, WW);
    if(BB > WW) return 1;
    if(BB < WW) return -1;
    if(BB && WW)    return 0;
    // four of a kind
    if(b[0] == b[3] || b[1] == b[4])
        BB = b[1];
    if(w[0] == w[3] || w[1] == w[4])
        WW = w[1];
    //printf("four of a kind %d %d\n", BB, WW);
    if(BB > WW) return 1;
    if(BB < WW) return -1;
    if(BB && WW)    return 0;
    // full house
    if(b[0] == b[2] && b[3] == b[4])
        BB = b[0];
    if(b[0] == b[1] && b[2] == b[4])
        BB = b[2];
    if(w[0] == w[2] && w[3] == w[4])
        WW = w[0];
    if(w[0] == w[1] && w[2] == w[4])
        WW = w[2];
    //printf("full house %d %d\n", BB, WW);
    if(BB > WW) return 1;
    if(BB < WW) return -1;
    if(BB && WW)    return 0;
    // flush
    if(fb[0] == fb[4])
        BB = 1;
    if(fw[0] == fw[4])
        WW = 1;
    //printf("fush %d %d\n", BB, WW);
    if(BB > WW) return 1;
    if(BB < WW) return -1;
    if(BB == 1 && WW == 1) {
        for(int i = 4; i >= 0; i--) {
            if(b[i] > w[i]) return 1;
            if(w[i] > b[i]) return -1;
        }
        return 0;
    }
    // straight
    if(b[0]+4 == b[4])
        BB = b[4];
    if(w[0]+4 == w[4])
        WW = w[4];
    //printf("straight %d %d\n", BB, WW);
    if(BB > WW) return 1;
    if(BB < WW) return -1;
    if(BB && WW)    return 0;
    // three of a kind
    for(int i = 0; i < 3; i++)
        if(b[i] == b[i+2])
            BB = b[i];
    for(int i = 0; i < 3; i++)
        if(w[i] == w[i+2])
            WW = w[i];
    //printf("three of a kind %d %d\n", BB, WW);
    if(BB > WW) return 1;
    if(BB < WW) return -1;
    if(BB && WW)    return 0;
    // two pairs
    if(b[0] == b[1] && b[2] == b[3])
        a1 = b[0], b1 = b[2], c1 = b[4], BB = 1;
    if(b[0] == b[1] && b[3] == b[4])
        a1 = b[0], b1 = b[3], c1 = b[2], BB = 1;
    if(b[1] == b[2] && b[3] == b[4])
        a1 = b[1], b1 = b[3], c1 = b[0], BB = 1;
    if(w[0] == w[1] && w[2] == w[3])
        a2 = w[0], b2 = w[2], c2 = w[4], WW = 1;
    if(w[0] == w[1] && w[3] == b[4])
        a2 = w[0], b2 = w[3], c2 = w[2], WW = 1;
    if(w[1] == w[2] && w[3] == b[4])
        a2 = w[1], b2 = w[3], c2 = w[0], WW = 1;
    //printf("two pair %d %d\n", BB, WW);
    if(BB > WW) return 1;
    if(BB < WW) return -1;
    if(BB && WW) {
        if(b1 != b2)    return b1 > b2 ? 1 : -1;
        if(a1 != a2)    return a1 > a2 ? 1 : -1;
        if(c1 > c2) return 1;
        if(c1 < c2) return -1;
        return 0;
    }
    // one pair
    if(b[0] == b[1])
        BB = 1, a1 = b[0], b1 = b[2], c1 = b[3], d1 = b[4];
    if(b[1] == b[2])
        BB = 1, a1 = b[1], b1 = b[0], c1 = b[3], d1 = b[4];
    if(b[2] == b[3])
        BB = 1, a1 = b[2], b1 = b[0], c1 = b[1], d1 = b[4];
    if(b[3] == b[4])
        BB = 1, a1 = b[3], b1 = b[0], c1 = b[1], d1 = b[2];
    if(w[0] == w[1])
        WW = 1, a2 = w[0], b2 = w[2], c2 = w[3], d2 = w[4];
    if(w[1] == w[2])
        WW = 1, a2 = w[1], b2 = w[0], c2 = w[3], d2 = w[4];
    if(w[2] == w[3])
        WW = 1, a2 = w[2], b2 = w[0], c2 = w[1], d2 = w[4];
    if(w[3] == w[4])
        WW = 1, a2 = w[3], b2 = w[0], c2 = w[1], d2 = w[2];
    //printf("one pair %d %d\n", BB, WW);
    if(BB > WW) return 1;
    if(BB < WW) return -1;
    if(BB && WW) {
        if(a1 != a2)    return a1 > a2 ? 1 : -1;
        if(d1 != d2)    return d1 > d2 ? 1 : -1;
        if(c1 != c2)    return c1 > c2 ? 1 : -1;
        if(b1 != b2)    return b1 > b2 ? 1 : -1;
        if(a1 != a2)    return a1 > a2 ? 1 : -1;
        return 0;
    }
    for(int i = 4; i >= 0; i--) {
        if(b[i] > w[i]) return 1;
        if(w[i] > b[i]) return -1;
    }
    return 0;

}
int main() {
    int i, j, k;
    char s[1024], B[5][3], W[5][3];
    while(1) {
        for(i = 0; i < 5; i++) {
            if(scanf("%s", B[i]) == 1);
            else    return 0;
            b[i] = s2n(B[i][0]), fb[i] = B[i][1];
        }
        for(i = 0; i < 5; i++) {
            scanf("%s", W[i]);
            w[i] = s2n(W[i][0]), fw[i] = W[i][1];
        }
        int flag = solve();
        if(flag == 1)
            puts("Black wins.");
        else if(flag == -1)
            puts("White wins.");
        else
            puts("Tie.");
    }
    return 0;
}
