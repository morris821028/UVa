#include <stdio.h>
#include <stdlib.h>
#include <map>
using namespace std;

int main() {
    map<int, int> record[60][30];
    int n, i, j, A[60][30];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < 2*n-1; i++) {
            for(j = 0; j < n-abs(n-i-1); j++) {
                scanf("%d", &A[i][j]);
                A[i][j] = abs(A[i][j]);
                record[i][j].clear();
            }
        }
        record[2*n-2][0][A[2*n-2][0]] = 1;
        for(i = 2*n-2; i >= n; i--) {
            for(j = 0; j < n-abs(n-i-1); j++) {
                for(map<int, int>::iterator k = record[i][j].begin(); k != record[i][j].end(); k++) {
                    int v = k->first;
                    record[i-1][j][abs(v+A[i-1][j])] = 1;
                    record[i-1][j][abs(v-A[i-1][j])] = 1;
                    record[i-1][j+1][abs(v+A[i-1][j+1])] = 1;
                    record[i-1][j+1][abs(v-A[i-1][j+1])] = 1;
                }
            }
        }
        for(i = n-1; i >= 1; i--) {
            for(j = 0; j < n-abs(n-i-1); j++) {
                for(map<int, int>::iterator k = record[i][j].begin(); k != record[i][j].end(); k++) {
                    int v = k->first;
                    record[i-1][j][abs(v+A[i-1][j])] = 1;
                    record[i-1][j][abs(v-A[i-1][j])] = 1;
                    if(j) {
                        record[i-1][j-1][abs(v+A[i-1][j-1])] = 1;
                        record[i-1][j-1][abs(v-A[i-1][j-1])] = 1;
                    }
                }
            }
        }
        int min = 0xfffffff;
        for(map<int, int>::iterator i = record[0][0].begin(); i != record[0][0].end(); i++)
            if(abs(i->first) < min)
                min = abs(i->first);
        printf("%d\n", min);
    }
    return 0;
}
