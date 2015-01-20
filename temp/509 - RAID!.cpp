#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
using namespace std;

char mem[128][65536];
int main() {
    int cases = 0;
    int D, S, B;
    char kind[8];
    while (scanf("%d %d %d", &D, &S, &B) == 3 && D) {
        scanf("%s", kind);
        for (int i = 0; i < D; i++)
            scanf("%s", mem[i]);
        int n = S * B, kv = kind[0] == 'E' ? 0 : 1;
        int err = 0;
        for (int i = 0, j = 0; i < n; i += S, j++) {
            j %= D;
            for (int p = i; p < i + S; p++) {
                int broken = 0, brokenPos = 0, XOR = 0;
                for (int k = 0; k < D; k++) {
                    if (mem[k][p] == 'x')
                        broken++, brokenPos = k;
                    else
                        XOR ^= mem[k][p] - '0';
                }
                if (broken >= 2)
                    err = 1;
                else if (broken == 1) {
                    if (brokenPos == j) {

                    } else {
                        mem[brokenPos][p] = '0' + (kv^XOR);
                    }
                } else {
                    if (XOR != kv)  err = 1;
                }
            }
        }
        printf("Disk set %d is ", ++cases);
        if (err) {
            puts("invalid.");
        } else {
            char buff[65536];
            memset(buff, '0', sizeof(buff));
            int m = 0;
            for (int i = 0, j = 0; i < n; i += S, j++) {
                j %= D;
                for (int k = 0; k < D; k++) {
                    if (k == j) continue;
                    for (int p = i; p < i + S; p++) {
                        buff[m++] = mem[k][p];
                    }
                }
            }
            printf("valid, contents are: ");
            for (int i = 0; i < m; i += 4) {
                int val = 0;
                val |= (buff[i + 0] - '0') << 3;
                val |= (buff[i + 1] - '0') << 2;
                val |= (buff[i + 2] - '0') << 1;
                val |= (buff[i + 3] - '0') << 0;
                printf("%X", val);
            }
            puts("");
        }
    }
    return 0;
}
/*
 
 5 2 5
 E
 xx01011111
 0110111011
 1011011111
 1110101100
 0010010111
 5 2 5
 E
 0001011111
 0110111011
 1011011111
 1110101100
 0010010111
 3 2 5
 E
 0001111111
 0111111011
 xx11011111
 3 5 1
 O
 11111
 11xxx
 x1111
 0
*/