#include <stdio.h>
#include <stdlib.h>
#include <map>
using namespace std;

int main() {
    map<int, int> record1[60][30], record2[60][30];
    int n, i, j, A[60][30];
    while(scanf("%d", &n) == 1 && n) {
        for(i = 0; i < 2*n-1; i++) {
            for(j = 0; j < n-abs(n-i-1); j++) {
                scanf("%d", &A[i][j]);
                A[i][j] = abs(A[i][j]);
                record1[i][j].clear();
                record2[i][j].clear();
            }
        }
        if(n == 1) {
            printf("%d\n", A[0][0]);
            continue;
        }
        record1[2*n-2][0][A[2*n-2][0]] = 1;
        for(i = 2*n-2; i >= n; i--) {
            for(j = 0; j < n-abs(n-i-1); j++) {
                for(map<int, int>::iterator k = record1[i][j].begin(); k != record1[i][j].end(); k++) {
                    int v = k->first;
                    record1[i-1][j][abs(v+A[i-1][j])] = 1;
                    record1[i-1][j][abs(v-A[i-1][j])] = 1;
                    record1[i-1][j+1][abs(v+A[i-1][j+1])] = 1;
                    record1[i-1][j+1][abs(v-A[i-1][j+1])] = 1;
                }
            }
        }
        record2[0][0][A[0][0]] = 1;
        for(i = 0; i <= n-1; i++) {
            for(j = 0; j < n-abs(n-i-1); j++) {
                for(map<int, int>::iterator k = record2[i][j].begin(); k != record2[i][j].end(); k++) {
                    int v = k->first;
                    record2[i+1][j][abs(v+A[i+1][j])] = 1;
                    record2[i+1][j][abs(v-A[i+1][j])] = 1;
                    record2[i+1][j+1][abs(v+A[i+1][j+1])] = 1;
                    record2[i+1][j+1][abs(v-A[i+1][j+1])] = 1;
                }
            }
        }
        int min = 0xfffffff;
        for(i = 0; i < n; i++) {
            for(map<int, int>::iterator j = record1[n][i].begin(); j != record1[n][i].end(); j++) {
                if(min == 0)    break;
                for(map<int, int>::iterator k = record2[n-1][i].begin(); k != record2[n-1][i].end(); k++) {
                    int v1 = j->first, v2 = k->first;
                    if(abs(v1-v2) < min)
                        min = abs(v1-v2);
                }
                for(map<int, int>::iterator k = record2[n-1][i+1].begin(); k != record2[n-1][i+1].end(); k++) {
                    int v1 = j->first, v2 = k->first;
                    if(abs(v1-v2) < min)
                        min = abs(v1-v2);
                }
            }
        }
        printf("%d\n", min);
    }
    return 0;
}
