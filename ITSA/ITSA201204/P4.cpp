#include <stdio.h>
#include <sstream>
#include <iostream>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    getchar();
    while(n--) {
        string line;
        getline(cin, line);
        stringstream sin1(line);
        int cntA[101] = {}, cntB[101] = {}, x;
        int A = 0, B = 0;
        while(sin1 >> x) {
            cntA[x] = 1, A++;
        }
        getline(cin, line);
        stringstream sin2(line);
        while(sin2 >> x) {
            cntB[x] = 1, B++;
        }
        int same = 0;
        for(int i = 0; i <= 100; i++)
            if(cntB[i] == 1 && cntA[i] == 1)
                same++;
        if(same == A && A != B)
            printf("1\n");
        else if(same == B && A != B)
            printf("2\n");
        else if(same == A && A == B)
            printf("3\n");
        else if(same == 0)
            printf("4\n");
        else
            printf("5\n");
    }
    return 0;
}/*
5
5 4 3 2 1
1 2 3 4 5
11 13 17 19 23 29 31 37
41 43 47
9 8 5 12 13 15 16
33 41 47 89 99 85 56 5 12 13 14 15
11 12 13
11 12 13 14 15
66 68 70 72 74 76 78 80
70 72 74
*/
